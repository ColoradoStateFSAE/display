#include "Motion.h"

using namespace std;

Motion::Motion(string filename) : filename(filename) {
	if((file = open("/dev/i2c-1", O_RDWR)) < 0) {
		qDebug() << "Motion: /dev/i2c-1 error";
		motionError = true;
	}
	
	ioctl(file, I2C_SLAVE, ADDRESS);
	
	i2c_smbus_write_byte_data(file, PWR_MGMT_1, 1);
	i2c_smbus_write_byte_data(file, CONFIG, 0);
	i2c_smbus_write_byte_data(file, ACCEL_CONFIG, 0x08);
	
	string motionFilename = "/root/log/" + filename + "motion.txt";
	motionFile = ofstream(motionFilename, ios::app);
	motionFile << "time (s),ax (g),ay (g),az (g)" << '\n';
}

int Motion::read_raw_data(int addr) {
	int high = i2c_smbus_read_byte_data(file, addr);
	int low = i2c_smbus_read_byte_data(file, addr + 1);
	int value = (high << 8) | low;

	if (value > 32768)
		value -= 65536;

	return value;
}

void Motion::start() {
	while (true) {
		try {
			double ax = read_raw_data(ACCEL_XOUT_H) / 8192.0;
			double ay = read_raw_data(ACCEL_YOUT_H) / 8192.0;
			double az = read_raw_data(ACCEL_ZOUT_H) / 8192.0;

			static auto startTime = QDateTime::currentMSecsSinceEpoch();
			double time = (QDateTime::currentMSecsSinceEpoch() - startTime) / 1000.0;
			buffer += to_string(time) + "," + to_string(ax) + ',' + to_string(ay) + ',' + to_string(az);

			if(buffer.size() > 0) {
				motionFile << buffer << endl;
				buffer = "";
			}
		} catch (...) {

		}
	}
}
