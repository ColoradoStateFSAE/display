#include "ViewModel.h"

using namespace std;

ViewModel::ViewModel(Navigation &navigation, QObject* parent) : QObject(parent), navigation(navigation) {
	time.start();
	lastShiftUpdate = time.elapsed();
	lastCanUpdate = time.elapsed();
	lastControllerUpdate = time.elapsed();
	
	string filename = get_filename();
	string canFilename = "/root/log/" + filename + "can.txt";
	canFile = ofstream(canFilename, ios::app);
	
	// // NeoPixel
	NeoPixel *neoPixel = new NeoPixel(10000, 14000);
	QObject::connect(&neoPixelThread, &QThread::started, neoPixel, &NeoPixel::start);
	neoPixel->moveToThread(&neoPixelThread);
	neoPixelThread.start();
	
	QObject::connect(this, &ViewModel::rpmChanged, neoPixel, &NeoPixel::rpmReceived);
	QObject::connect(this, &ViewModel::batteryChanged, neoPixel, &NeoPixel::batteryReceived);
	QObject::connect(this, &ViewModel::coolantChanged, neoPixel, &NeoPixel::coolantReceived);
	QObject::connect(this, &ViewModel::brightnessChanged, neoPixel, &NeoPixel::brightnessReceived);
	QObject::connect(this, &ViewModel::estopChanged, neoPixel, &NeoPixel::estopReceived);
	QObject::connect(this, &ViewModel::shiftingSystemOffline, neoPixel, &NeoPixel::shiftingReceived);
	QObject::connect(this, &ViewModel::shiftControllerOffline, neoPixel, &NeoPixel::shiftControllerReceived);
	QObject::connect(this, &ViewModel::ecuOffline, neoPixel, &NeoPixel::ecuReceived);

	
	// Update the screen every 17 ms
	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, [&]() {
		emit longitudinalGChanged(longitudinalG);
		emit lateralGChanged(lateralG);
		emit verticalGChanged(verticalG);

		// Do not update if the task switcher is active
		if(navigation.taskSwitcher) return;

		if(time.elapsed() - lastControllerUpdate > 500) {
			emit shiftControllerOffline(true);
		} else {
			emit shiftControllerOffline(false);
		}
		
		if(time.elapsed() - lastShiftUpdate > 500) {
			emit shiftingSystemOffline(true);
		} else {
			emit shiftingSystemOffline(false);
		}
		
		if(time.elapsed() - lastCanUpdate > 500) {
			emit ecuOffline(true);
			emit batteryChanged(14);
		} else {
			emit ecuOffline(false);
			emit gearChanged(gear);
			emit rpmChanged(rpm);
			emit oilChanged(oil);
			emit coolantChanged(coolant);
			emit tpsChanged(tps);
			emit batteryChanged(battery);
			emit afrChanged(afr);
			emit clutchChanged(clutch);
			emit neutralChanged(neutral);
			emit estopChanged(estop);
			emit etcChanged(etcError);
		}
	});
	timer->start(16);

	// Save buffer every 5 seconds
	QTimer *bufferTimer = new QTimer(this);
	connect(bufferTimer, &QTimer::timeout, this, [&](){
		canFile << buffer.str();
		canFile.flush();
	});
	bufferTimer->start(5000);
}

string ViewModel::get_filename() {
	const filesystem::path dir = "/root/log";

	if (!filesystem::exists(dir)) filesystem::create_directory(dir);

	int maxNumber = 0;

	for (const auto& entry : std::filesystem::directory_iterator(dir)) {
		if (entry.is_regular_file()) {
			auto current = stoi(entry.path().filename().string().substr(0, 4));

			if (current > maxNumber) {
				maxNumber = current;
			}
		}
	}

	stringstream fileNumber;
	maxNumber += 1;
	if (maxNumber != 0) {
		fileNumber << setfill('0') << setw(4) << maxNumber;
	} else {
		fileNumber << "0000";
	}

	return fileNumber.str();
}

void ViewModel::frameReceived(const QCanBusFrame &frame) {
	int id = frame.frameId();
	auto data = reinterpret_cast<const uint8_t*>(frame.payload().constData());
	
	switch(id) {
		case TCS_CLUTCH_FRAME_ID: {
			lastShiftUpdate = time.elapsed();
			tcs_clutch_t message;
			tcs_clutch_unpack(&message, data, frame.payload().size());

			clutch = tcs_clutch_position_percentage_decode(message.position_percentage);
			break;
		}

		case TCS_SHIFT_CONTROLLER_FRAME_ID: {
			lastControllerUpdate = time.elapsed();
			tcs_shift_controller_t message;
			break;
		}
		
		case R3_GROUP00_FRAME_ID: {
			lastCanUpdate = time.elapsed();
			r3_group00_t message;
			r3_group00_unpack(&message, data, frame.payload().size());
			
			rpm = r3_group00_rpm_decode(message.rpm);
			tps = r3_group00_throttle_position_decode(message.throttle_position);
			break;
		}
		
		case R3_GROUP01_FRAME_ID: {
			r3_group01_t message;
			r3_group01_unpack(&message, data, frame.payload().size());
			
			oil = r3_group01_oil_pressure_decode(message.oil_pressure);
			// oil = convert::kpa_to_psi(oil);
			break;
		}

		case R3_GROUP15_FRAME_ID: {
			r3_group15_t message;
			r3_group15_unpack(&message, data, frame.payload().size());
			auto data = reinterpret_cast<const uint8_t*>(frame.payload().constData());
			size_t dataLength = frame.payload().size();

			battery = r3_group15_battery_voltage_decode(message.battery_voltage);
			break;
		}

		case R3_GROUP20_FRAME_ID: {
			r3_group20_t message;
			r3_group20_unpack(&message, data, frame.payload().size());
			
			coolant = r3_group20_coolant_temperature_decode(message.coolant_temperature);
			coolant = convert::k_to_f(coolant);
			break;
		}

		case R3_GROUP24_FRAME_ID: {
			r3_group24_t message;
			r3_group24_unpack(&message, data, frame.payload().size());
			
			neutral = r3_group24_neutral_switch_decode(message.neutral_switch);
			break;
		}
		case R3_GROUP39_FRAME_ID: {
			r3_group39_t message;
			r3_group39_unpack(&message, data, frame.payload().size());
			
			gear = r3_group39_gear_decode(message.gear);
			break;
		}
		case R3_GROUP08_FRAME_ID: {
            r3_group08_t message;
            r3_group08_unpack(&message, data, frame.payload().size());

            lateralG = r3_group08_lateral_g_decode(message.lateral_g) / 9.81;
            break;
        }

        case R3_GROUP11_FRAME_ID: {
            r3_group11_t message;
            r3_group11_unpack(&message, data, frame.payload().size());

            longitudinalG = r3_group11_longitudinal_g_decode(message.longitudinal_g) / 9.81;
            break;
        }

        case R3_GROUP43_FRAME_ID: {
            r3_group43_t message;
            r3_group43_unpack(&message, data, frame.payload().size());

            verticalG = r3_group43_vertical_g_decode(message.vertical_g) / 9.81;
            break;
        }

		case R3_GROUP27_FRAME_ID: {
			r3_group27_t message;
			r3_group27_unpack(&message, data, frame.payload().size());

			estop = r3_group27_generic_sensor_1_decode(message.generic_sensor_1);
			etcError = r3_group27_generic_sensor_2_decode(message.generic_sensor_2);
		}

	}
	
	if(neutral) {
		gear = 0;
	}
	// logFrame(frame);
}

void ViewModel::setBrightness(int value) {
	if (brightness != value) {
		brightness = value;
		emit brightnessChanged(value);
	}
}

void ViewModel::logFrame(const QCanBusFrame &frame) {
	QString hexString;

	for (const char byte : frame.payload()) {
		hexString.append(QString::number(static_cast<quint8>(byte), 16).rightJustified(2, '0').toUpper() + " ");
	}

	auto timeStamp = frame.timeStamp();
	double seconds = timeStamp.seconds() + timeStamp.microSeconds() / 1000000.0;

	QString formattedTime = QString::number(seconds, 'f', 3);

	buffer << formattedTime.toStdString() << " " << frame.frameId() << " " << hexString.trimmed().toStdString() << '\n';
}
