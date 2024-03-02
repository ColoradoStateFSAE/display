#ifndef ENCODER_H
#define ENCODER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>

extern "C" {
	#include <linux/i2c.h>
	#include <linux/i2c-dev.h>
	#include <i2c/smbus.h>
}

class Encoder : public QObject {
	Q_OBJECT

private:
	const char I2C_ADDRESS = 0x36;
	const char ENCODER_BASE = 0x11;
	const char ENCODER_DELTA = 0x40;
	const char GPIO_BASE = 0x01;
	const char GPIO_BULK = 0x04;

	bool encoderError = false;
	int file;
	bool lastState = false;

	bool initialize_encoder();
	void read_encoder();
	void read_button();

public slots:
	void start();

signals:
	void encoderChanged(int value);
	void buttonPressed();
};

#endif // ENCODER_H
