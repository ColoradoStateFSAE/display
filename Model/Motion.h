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
    Motion(std::string filename) : filename(filename) {
        if((file = open("/dev/i2c-1", O_RDWR)) < 0) {
            qDebug() << "Motion: /dev/i2c-1 error";
            motionError = true;
        }

        ioctl(file, I2C_SLAVE, ADDRESS);

        i2c_smbus_write_byte_data(file, PWR_MGMT_1, 1);
        i2c_smbus_write_byte_data(file, CONFIG, 0);
        i2c_smbus_write_byte_data(file, ACCEL_CONFIG, 0x08);

        std::string motionFilename = "/root/log/" + filename + "motion.txt";
        motionFile = std::ofstream(motionFilename, std::ios::app);
        motionFile << "time (s),ax (g),ay (g),az (g)" << '\n';
    }

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
