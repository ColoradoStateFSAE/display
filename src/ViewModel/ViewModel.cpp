#include "ViewModel.h"

using namespace std;

ViewModel::ViewModel(Navigation &navigation, QObject* parent) : QObject(parent), navigation(navigation) {
	time.start();
	lastShiftUpdate = time.elapsed();
	lastCanUpdate = time.elapsed();
	
	string filename = get_filename();
	string canFilename = "/root/log/" + filename + "can.txt";
	canFile = ofstream(canFilename, ios::app);
	
	// // NeoPixel
	NeoPixel *neoPixel = new NeoPixel(7000, 9200);
	QObject::connect(&neoPixelThread, &QThread::started, neoPixel, &NeoPixel::start);
	neoPixel->moveToThread(&neoPixelThread);
	neoPixelThread.start();
	
	QObject::connect(this, &ViewModel::rpmChanged, neoPixel, &NeoPixel::rpmReceived);
	QObject::connect(this, &ViewModel::batteryChanged, neoPixel, &NeoPixel::batteryReceived);
	QObject::connect(this, &ViewModel::coolantChanged, neoPixel, &NeoPixel::coolantReceived);
	QObject::connect(this, &ViewModel::shiftReceived, neoPixel, &NeoPixel::shiftReceived);
	
	// GPS
	Gps gps(filename);
	
	// Motion
	Motion *motion = new Motion(filename);
	QObject::connect(&motionThread, &QThread::started, motion, &Motion::start);
	motion->moveToThread(&motionThread);
	motionThread.start();
	
	// Update the screen every 17 ms
	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, [&]() {
		// Do not update if the task switcher is active
		if(navigation.taskSwitcher) return;
		
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
			emit advanceChanged(advance);
			emit coolantChanged(coolant);
			emit tpsChanged(tps);
			emit batteryChanged(battery);
			emit afrChanged(afr);
			emit clutchChanged(clutch);
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
		case 522: {
			if(data[0] == 1) {
				emit shiftReceived();
			}
			break;
		}
			
		case TCS_GEAR_FRAME_ID: {
			lastShiftUpdate = time.elapsed();
			tcs_gear_t message;
			tcs_gear_unpack(&message, data, sizeof(message));
			
			gear = tcs_gear_gear_decode(message.gear);
			break;
		}
		
		case MS3X_MEGASQUIRT_GP0_FRAME_ID: {
			lastCanUpdate = time.elapsed();
			ms3x_megasquirt_gp0_t message;
			ms3x_megasquirt_gp0_unpack(&message, data, sizeof(message));
			
			rpm = ms3x_megasquirt_gp0_rpm_decode(message.rpm);
			break;
		}
		
		case MS3X_MEGASQUIRT_GP1_FRAME_ID: {
			ms3x_megasquirt_gp1_t message;
			ms3x_megasquirt_gp1_unpack(&message, data, sizeof(message));
			
			advance = ms3x_megasquirt_gp1_adv_deg_decode(message.adv_deg);
			break;
		}
			
		case MS3X_MEGASQUIRT_GP2_FRAME_ID: {
			ms3x_megasquirt_gp2_t message;
			ms3x_megasquirt_gp2_unpack(&message, data, sizeof(message));
			
			coolant = ms3x_megasquirt_gp2_clt_decode(message.clt);
			break;
		}
			
		case MS3X_MEGASQUIRT_GP3_FRAME_ID: {
			ms3x_megasquirt_gp3_t message;
			ms3x_megasquirt_gp3_unpack(&message, data, sizeof(message));
			
			battery = ms3x_megasquirt_gp3_batt_decode(message.batt);
			tps = ms3x_megasquirt_gp3_tps_decode(message.tps);
			break;
		}
			
		case MS3X_MEGASQUIRT_GP31_FRAME_ID: {
			ms3x_megasquirt_gp31_t message;
			ms3x_megasquirt_gp31_unpack(&message, data, sizeof(message));
			
			afr = ms3x_megasquirt_gp31_afr1_decode(message.afr1);
			break;
		}
		
		case TCS_CLUTCH_FRAME_ID: {
			tcs_clutch_t message;
			tcs_clutch_unpack(&message, data, sizeof(message));

			clutch = tcs_clutch_position_percentage_decode(message.position_percentage);
			break;
		}	
	}
	
	// logFrame(frame);
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
