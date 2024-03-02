#ifndef MOTION_H
#define MOTION_H

#include <QDebug>
#include <QDateTime>
#include <fstream>
#include <fcntl.h>
#include <sys/ioctl.h>

extern "C" {
	#include <linux/i2c.h>
	#include <linux/i2c-dev.h>
	#include <i2c/smbus.h>
}

class Motion : public QObject {
	Q_OBJECT

public:
	Motion(std::string filename);
	
private:
	int file;
	const char *bus = "/dev/i2c-1";
	const int ADDRESS = 0x68;

	const int PWR_MGMT_1 = 0x6B;
	const int CONFIG = 0x1A;
	const int ACCEL_CONFIG = 0x1C;
	const int GYRO_CONFIG = 0x1B;
	const int ACCEL_XOUT_H = 0x3B;
	const int ACCEL_YOUT_H = 0x3D;
	const int ACCEL_ZOUT_H = 0x3F;
	const int GYRO_XOUT_H = 0x43;
	const int GYRO_YOUT_H = 0x45;
	const int GYRO_ZOUT_H = 0x47;

	std::string filename;
	std::ofstream motionFile;
	std::string buffer = "";

	bool motionError = false;

	int read_raw_data(int addr);

public slots:
	void start();
};

#endif // MOTION_H
