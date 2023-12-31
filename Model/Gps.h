#ifndef GPS_H
#define GPS_H

#include <QtSerialPort/QSerialPort>

class Gps {
public:
    Gps(std::string filename) {
        serial.setPortName("ttyS0");
        serial.setBaudRate(QSerialPort::Baud9600);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::NoFlowControl);

        if (!serial.open(QIODevice::ReadOnly)) {
            qDebug() << "Failed to open serial port";
            return;
        }

        std::string gpsFilename = "/root/log/" + filename + "gps.txt";
        gpsFile = std::ofstream(gpsFilename, std::ios::app);

        QObject::connect(&serial, &QSerialPort::readyRead, [&]() {
            while (serial.canReadLine()) {
                QByteArray data = serial.readAll();

                if(data.startsWith("$GPRMC")) {
                    gpsFile << data.toStdString();
                    gpsFile.flush();
                }
            }
        });
    }

private:
    QSerialPort serial;
    std::ofstream gpsFile;
};

#endif // GPS_H
