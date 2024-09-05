#ifndef GPS_H
#define GPS_H

#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <fstream>

class Gps {
public:
	Gps() = delete;
	Gps(std::string filename);

private:
	QSerialPort serial;
	std::ofstream gpsFile;
};

#endif // GPS_H
