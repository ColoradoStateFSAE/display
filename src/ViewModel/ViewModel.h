#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QTimer>
#include <fstream>
#include <filesystem>
#include <QDateTime>
#include <sstream>
#include "../Navigation/Navigation.h"
#include "../NeoPixel/NeoPixel.h"
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
	void longitudinalGChanged(float value);
	void lateralGChanged(float value);
	void verticalGChanged(float value);
	void brightnessChanged(int value);
	void neutralChanged(int value);
	void shiftReceived();
	void ecuOffline(bool state);
	void shiftingSystemOffline(bool state);
	void shiftControllerOffline(bool state);
	void estopChanged(int value);
	void etcChanged(int value);

public:
	ViewModel(Navigation &navigation, QObject* parent = nullptr);
	void frameReceived(const QCanBusFrame &frame);
	int getBrightness() const { return brightness; }
	void setBrightness(int value);

private:
	QElapsedTimer time;
	qint64 lastCanUpdate;
	qint64 lastShiftUpdate;
	qint64 lastControllerUpdate;
	std::ofstream canFile;
	Navigation &navigation;
	QThread neoPixelThread;
	QThread motionThread;
	std::stringstream buffer;

	int neutral = 0;
	int gear = 0;
	float rpm = 0;
	float battery = 0;
	float coolant = 0;
	float tps = 0;
	float afr = 0;
	float clutch = 0;
	float oil = 0;
	float longitudinalG = 0;
	float lateralG = 0;
	float verticalG = 0;
	int brightness = 0;
	int estop = 0;
	int etcError = 0;

	std::string get_filename();
	void logFrame(const QCanBusFrame &frame);
};

#endif // VIEWMODEL_H
