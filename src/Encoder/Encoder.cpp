#include "Encoder.h"

using namespace std;

bool Encoder::initialize_encoder() {
	if((file = open("/dev/i2c-1", O_RDWR)) < 0) {
		qDebug() << "Encoder: /dev/i2c-1 error";
		encoderError = true;
		return false;
	}

	if(ioctl(file, I2C_SLAVE, I2C_ADDRESS) < 0) {
		qDebug() << "Encoder: I2C device error";
		encoderError = true;
		return false;
	}
	
	return true;
}

void Encoder::read_encoder() {
	i2c_smbus_write_byte_data(file, ENCODER_BASE, ENCODER_DELTA);

	uint8_t buffer[4];
	if (read(file, buffer, 4) != 4) {
		qDebug() << "Encoder: Read error";
		encoderError = true;
		return;
	} else {
		int value = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
		if (value != 0) {
			emit encoderChanged(-value);
		}
	}
}

void Encoder::read_button() {
	i2c_smbus_write_byte_data(file, GPIO_BASE, GPIO_BULK);

	uint8_t buffer[4];
	if (read(file, buffer, 4) != 4) {
		qDebug() << "Encoder: Button read error";
		return;
	} else {
		encoderError = false;
		bool state = !(buffer[0] & 0b00000001);
		if (state != lastState) {
			lastState = state;
			if (state) {
				emit buttonPressed();
			}
		}
	}
}

void Encoder::start() {
	initialize_encoder();

	while(!encoderError) {
		read_encoder();
		read_button();
	}
}
