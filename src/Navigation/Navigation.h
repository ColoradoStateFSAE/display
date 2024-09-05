#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QObject>
#include <QCanBus>
#include <QTimer>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "MenuItem.h"
#include "../Encoder/Encoder.h"
#include "../Util/canutil.h"
#include "../dbc/tcs.h"

class Navigation : public QObject {
  Q_OBJECT
  signals:
	void changeTaskSwitcher(bool);
	void cursorChanged(int, bool);
	void shiftChanged(int, int, int, int);
	void clutchChanged(int, int, int, int, int);

  public:
	enum State {
		EXIT,
		ABOUT,
		SHIFT,
		CLUTCH,

		UP_DELAY,
		DOWN_DELAY,
		OUTPUT,
		TIMEOUT,

		START,
		END,
		FRICTION,
		POSITION,
		AUTO_LAUNCH,
	};
	Q_ENUM(State)

	bool taskSwitcher = false;

	Navigation() { } ;
	Navigation(QCanBusDevice *device, QObject* parent = nullptr);
	void frameReceived(const QCanBusFrame &frame);

  private:
	QCanBusDevice *device;
	QThread encoderThread;

	MenuItem *current = &exit;

	MenuItem exit = MenuItem(EXIT, 0, [&](){ taskSwitcher = !taskSwitcher; changeTaskSwitcher(taskSwitcher); }).heading();
	MenuItem about = MenuItem(ABOUT, 0, [](){}).heading();

	MenuItem shift = MenuItem(SHIFT, 10, [&](){ current = &upDelay; }).heading();
	MenuItem upDelay = MenuItem(UP_DELAY, 10, [&](){ setShiftValues(); }, 0, 1000);
	MenuItem downDelay = MenuItem(DOWN_DELAY, 10, [&](){ setShiftValues(); }, 0, 1000);
	MenuItem output = MenuItem(OUTPUT, 10, [&](){ setShiftValues(); }, 0, 1000);
	MenuItem timeout = MenuItem(TIMEOUT, 10, [&](){ setShiftValues(); }, 0, 1000);

	MenuItem clutch = MenuItem(CLUTCH, 10, [&](){ current = &start; }).heading();
	MenuItem start = MenuItem(START, 10, [&](){ setClutchValues(); }, 0, 2000);
	MenuItem end = MenuItem(END, 10, [&](){ setClutchValues(); }, 0, 2000);
	MenuItem friction = MenuItem(FRICTION, 10, [&](){ setClutchValues(); }, 0, 2000);
	MenuItem position = MenuItem(POSITION, 10, [&](){ setClutchPosition(1); }, 0, 2000);
	MenuItem autoLaunch = MenuItem(AUTO_LAUNCH, 1, [&](){ setClutchValues(); }, 0, 1);

	QList<QCanBusDevice::Filter> filter();
	void encoderReceived(int value);
	void buttonPressReceived();
	void configureNavigation();
	void startUpdates();

	void setShiftValues();
	void setClutchValues();
	void setClutchPosition(int state=0);
};

#endif // NAVIGATION_H
