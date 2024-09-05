#include "Navigation.h"

using namespace std;

Navigation::Navigation(QCanBusDevice *device, QObject* parent) : QObject(parent), device(device) {
	// Encoder
	Encoder *encoderModel = new Encoder();
	QObject::connect(&encoderThread, &QThread::started, encoderModel, &Encoder::start);
	encoderModel->moveToThread(&encoderThread);
	encoderThread.start();

	QObject::connect(encoderModel, &Encoder::encoderChanged, this, &Navigation::encoderReceived, Qt::QueuedConnection);
	QObject::connect(encoderModel, &Encoder::buttonPressed, this, &Navigation::buttonPressReceived, Qt::QueuedConnection);

	configureNavigation();
	startUpdates();
}

void Navigation::encoderReceived(int value) {
	if(!taskSwitcher) return;

	if(current->selected) {
		current->change(value);

		// Special case to send clutch position immediately
		if(current->id == position.id) {
			setClutchPosition(0);
		}
	} else {
		if(value == 1) {
			if(current->next != nullptr) current = current->next;
		} else {
			if(current->previous != nullptr) current = current->previous;
		}
	}
}

void Navigation::buttonPressReceived() {
	static int count = 0;
	
	if(current->isHeading()) {
		current->action();
	} else {
		current->selected = !current->selected;
		if(!current->selected) {
			current->action();
		}
	}
}

void Navigation::configureNavigation() {
		// Headings
		exit.next = &about;

		about.previous = &exit;
		about.next = &shift;

		shift.previous = &about;
		shift.next = &clutch;

		clutch.previous = &shift;

		// Shift
		upDelay.previous = &shift;
		upDelay.next = &downDelay;
		
		downDelay.previous = &upDelay;
		downDelay.next = &output;

		output.previous = &downDelay;
		output.next = &timeout;

		timeout.previous = &output;

		// Clutch
		start.previous = &clutch;
		start.next = &end;
		
		end.previous = &start;
		end.next = &friction;

		friction.previous = &end;
		friction.next = &position;

		position.previous = &friction;
		position.next = &autoLaunch;

		autoLaunch.previous = &position;
	}

void Navigation::startUpdates() {
	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, [&]() {
		// Do not update if the task switcher is inactive
		if(!taskSwitcher) return;
		
		emit cursorChanged(current->id, current->selected);
		emit shiftChanged(upDelay.value, downDelay.value, output.value, timeout.value);
		emit clutchChanged(start.value, end.value, friction.value, position.value, autoLaunch.value);
	});
	timer->start(16);
}

void Navigation::frameReceived(const QCanBusFrame &frame) {
	// Early return if the task switcher is inactive or a task is selected
	if(!taskSwitcher || current->selected) return;

	const uint8_t* data = reinterpret_cast<const uint8_t*>(frame.payload().constData());

	switch(frame.frameId()) {
		case TCS_SHIFT_SETTINGS_FRAME_ID: {
			tcs_shift_settings_t message;
			tcs_shift_settings_unpack(&message, data, frame.payload().size());
			upDelay.value = tcs_shift_settings_up_delay_decode(message.up_delay);
			downDelay.value = tcs_shift_settings_down_delay_decode(message.down_delay);
			output.value = tcs_shift_settings_output_decode(message.output);
			timeout.value = tcs_shift_settings_timeout_decode(message.timeout);
			break;
		}
		
		case TCS_CLUTCH_SETTINGS_FRAME_ID: {
			tcs_clutch_settings_t message;
			tcs_clutch_settings_unpack(&message, data, frame.payload().size());
			start.value = tcs_clutch_settings_start_decode(message.start);
			end.value = tcs_clutch_settings_end_decode(message.end);
			friction.value = tcs_clutch_settings_friction_decode(message.friction);
			autoLaunch.value = tcs_clutch_settings_auto_launch_decode(message.auto_launch);
			break;
		}
			
		case TCS_CLUTCH_FRAME_ID: {
			tcs_clutch_t message;
			tcs_clutch_unpack(&message, data, frame.payload().size());
			position.value = tcs_clutch_position_decode(message.position);
			break;
		}
	}
}

void Navigation::setShiftValues() {
	QCanBusFrame frame;
	frame.setFrameId(TCS_SET_SHIFT_SETTINGS_FRAME_ID);

	tcs_set_shift_settings_t message;
	message.set_up_delay = tcs_set_shift_settings_set_up_delay_encode(upDelay.value);
	message.set_down_delay = tcs_set_shift_settings_set_down_delay_encode(downDelay.value);
	message.set_output = tcs_set_shift_settings_set_output_encode(output.value);
	message.set_timeout = tcs_set_shift_settings_set_timeout_encode(timeout.value);

	uint8_t payload[8] = {0};
	tcs_set_shift_settings_pack(payload, &message, sizeof(payload));
	frame.setPayload(QByteArray(reinterpret_cast<char*>(payload), sizeof(payload)));
	device->writeFrame(frame);
}

void Navigation::setClutchValues() {
	QCanBusFrame frame;
	frame.setFrameId(TCS_SET_CLUTCH_SETTINGS_FRAME_ID);

	tcs_set_clutch_settings_t message;
	message.set_start = tcs_set_clutch_settings_set_start_encode(start.value);
	message.set_end = tcs_set_clutch_settings_set_end_encode(end.value);
	message.set_friction = tcs_set_clutch_settings_set_friction_encode(friction.value);
	message.set_auto_launch = tcs_set_clutch_settings_set_auto_launch_encode(autoLaunch.value);

	uint8_t payload[8] = {0};
	tcs_set_clutch_settings_pack(payload, &message, sizeof(payload));
	frame.setPayload(QByteArray(reinterpret_cast<char*>(payload), sizeof(payload)));
	device->writeFrame(frame);
}

void Navigation::setClutchPosition(int state) {
	QCanBusFrame frame;
	frame.setFrameId(TCS_SET_CLUTCH_FRAME_ID);

	tcs_set_clutch_t message;
	message.set_position = tcs_set_clutch_set_position_encode(position.value);
	message.set_state = tcs_set_clutch_set_state_encode(state);

	uint8_t payload[8] = {0};
	tcs_set_clutch_pack(payload, &message, sizeof(payload));
	frame.setPayload(QByteArray(reinterpret_cast<char*>(payload), sizeof(payload)));
	device->writeFrame(frame);
}
