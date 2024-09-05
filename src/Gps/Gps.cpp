#include "Gps.h"

using namespace std;

Gps::Gps(string filename) {
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
	
	string gpsFilename = "/root/log/" + filename + "gps.txt";
	gpsFile = ofstream(gpsFilename, ios::app);
	
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
