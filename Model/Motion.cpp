#include "Motion.h"

using namespace std;

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
