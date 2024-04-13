#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QTimer>
#include <fstream>
#include <filesystem>
#include <QDateTime>
#include <sstream>
#include "../Navigation/Navigation.h"
#include "../NeoPixel/NeoPixel.h"
#include "../Gps/Gps.h"
#include "../Motion/Motion.h"
#include "../dbc/r3.h"
#include "../dbc/tcs.h"
#include "../Util/convert.h"

#include <QQuickWindow>
#include <QScreen>
#include <QImage>
#include <QPixmap>

class ViewModel : public QObject {
	Q_OBJECT

signals:
	void gearChanged(int value);
	void rpmChanged(int value);
	void batteryChanged(float value);
	void coolantChanged(float value);
	void tpsChanged(float value);
	void afrChanged(float value);
	void clutchChanged(float value);
	void oilChanged(float value);
	void shiftReceived();
	void ecuOffline(bool state);
	void shiftingSystemOffline(bool state);

public:
	ViewModel(Navigation &navigation, QObject* parent = nullptr);
	void frameReceived(const QCanBusFrame &frame);

private:
	QElapsedTimer time;
	qint64 lastCanUpdate;
	qint64 lastShiftUpdate;
	std::ofstream canFile;
	Navigation &navigation;
	QThread neoPixelThread;
	QThread motionThread;
	std::stringstream buffer;

	bool neutral = false;
	int gear = 0;
	float rpm = 0;
	float battery = 0;
	float coolant = 0;
	float tps = 0;
	float afr = 0;
	float clutch = 0;
	float oil = 0;

	std::string get_filename();
	void logFrame(const QCanBusFrame &frame);
};

#endif // VIEWMODEL_H
