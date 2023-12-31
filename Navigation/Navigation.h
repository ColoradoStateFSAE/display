#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <QObject>
#include <QCanBus>
#include <vector>
#include <cstdlib>

#include "MenuItem.h"
#include "Model/Encoder.h"
#include "Util/canutil.h"

class Navigation : public QObject {
    Q_OBJECT

    Q_PROPERTY(int EXIT READ getExit CONSTANT)
    Q_PROPERTY(int ABOUT READ getAbout CONSTANT)
    Q_PROPERTY(int SHIFT READ getShift CONSTANT)
    Q_PROPERTY(int CLUTCH READ getClutch CONSTANT)
    Q_PROPERTY(int UP_DELAY READ getUpDelay CONSTANT)
    Q_PROPERTY(int DOWN_DELAY READ getDownDelay CONSTANT)
    Q_PROPERTY(int OUTPUT READ getOutput CONSTANT)
    Q_PROPERTY(int TIMEOUT READ getTimeout CONSTANT)

    Q_PROPERTY(int POSITION READ getPosition CONSTANT)
    Q_PROPERTY(int START READ getStart CONSTANT)
    Q_PROPERTY(int END READ getEnd CONSTANT)
    Q_PROPERTY(int FRICTION READ getFriction CONSTANT)
    Q_PROPERTY(int AUTOLAUNCH READ getAutoLaunch CONSTANT)

    Q_PROPERTY(int upDelay READ getUpDelayValue NOTIFY updateMenu)
    Q_PROPERTY(int downDelay READ getDownDelayValue NOTIFY updateMenu)
    Q_PROPERTY(int output READ getOutputValue NOTIFY updateMenu)
    Q_PROPERTY(int timeout READ getTimeoutValue NOTIFY updateMenu)

    Q_PROPERTY(int position READ getPositionValue NOTIFY updateMenu)
    Q_PROPERTY(int start READ getStartValue NOTIFY updateMenu)
    Q_PROPERTY(int end READ getEndValue NOTIFY updateMenu)
    Q_PROPERTY(int friction READ getFrictionValue NOTIFY updateMenu)
    Q_PROPERTY(int autoLaunch READ getAutoLaunchValue NOTIFY updateMenu)

    Q_PROPERTY(bool selected READ getSelected NOTIFY updateMenu)

signals:
    void updateMenu();

    void changeTaskSwitcher(bool state);
    void changeCursor(int value);
    void changeSubmenu(int value);

public slots:
    void frameReceived();

public:
    Navigation() {
        // Encoder
        Encoder *encoderModel = new Encoder();
        QObject::connect(&encoderThread, &QThread::started, encoderModel, &Encoder::start);
        encoderModel->moveToThread(&encoderThread);
        encoderThread.start();

        QObject::connect(encoderModel, &Encoder::encoderChanged, this, &Navigation::encoderReceived, Qt::QueuedConnection);
        QObject::connect(encoderModel, &Encoder::buttonPressed, this, &Navigation::buttonPressReceived, Qt::QueuedConnection);

        // CAN
        QString errorString;
        device = QCanBus::instance()->createDevice(QStringLiteral("socketcan"), QStringLiteral("can0"), &errorString);
        device->setConfigurationParameter(QCanBusDevice::BitRateKey, QVariant());
        device->connectDevice();

        QObject::connect(device, &QCanBusDevice::framesReceived, this, &Navigation::frameReceived);
    }

    ~Navigation() {
        for (const auto& task : tasks) {
            for (MenuItem* menuItem : task) {
                delete menuItem;
            }
        }
    }

    bool taskSwitcher = false;

private:
    QCanBusDevice *device;
    QThread encoderThread;

    int getExit() { return exitHeading.id; }
    int getAbout() { return aboutHeading.id; }
    int getShift() { return shiftHeading.id; }
    int getClutch() { return clutchHeading.id; }

    int getUpDelay() { return upDelay.id; }
    int getDownDelay() { return downDelay.id; }
    int getOutput() { return output.id; }
    int getTimeout() { return timeout.id; }

    int getPosition() { return position.id; }
    int getStart() { return start.id; }
    int getEnd() { return end.id; }
    int getFriction() { return friction.id; }
    int getAutoLaunch() { return autoLaunch.id; }

    int getUpDelayValue() { return upDelay.value; }
    int getDownDelayValue() { return downDelay.value; }
    int getOutputValue() { return output.value; }
    int getTimeoutValue() { return timeout.value; }

    int getPositionValue() { return position.value; }
    int getStartValue() { return start.value; }
    int getEndValue() { return end.value; }
    int getFrictionValue() { return friction.value; }
    int getAutoLaunchValue() { return autoLaunch.value; }

    bool getSelected() {
        for (const auto& task : tasks) {
            for (MenuItem* menuItem : task) {
                if(menuItem->selected) return true;
            }
        }
        return false;
    }

    const int shiftIncrease = 10;
    const int clutchIncrease = 20;

    MenuItem exitHeading = MenuItem(0).heading();
    MenuItem aboutHeading = MenuItem(1).heading();
    MenuItem shiftHeading = MenuItem(2).heading();
    MenuItem clutchHeading = MenuItem(3).heading();

    MenuItem upDelay = MenuItem(4, shiftIncrease);
    MenuItem downDelay = MenuItem(5, shiftIncrease);
    MenuItem output = MenuItem(6, shiftIncrease);
    MenuItem timeout = MenuItem(7, shiftIncrease);

    MenuItem position = MenuItem(8, clutchIncrease);
    MenuItem start = MenuItem(9, clutchIncrease);
    MenuItem end = MenuItem(10, clutchIncrease);
    MenuItem friction = MenuItem(11, clutchIncrease);
    MenuItem autoLaunch = MenuItem(12);

    std::vector<MenuItem*> exit = {&exitHeading};
    std::vector<MenuItem*> about = {&aboutHeading};
    std::vector<MenuItem*> shift = {&shiftHeading, &upDelay, &downDelay, &output, &timeout};
    std::vector<MenuItem*> clutch = {&clutchHeading, &start, &end, &friction, &position, &autoLaunch};
    std::vector<std::vector<MenuItem*>> tasks = {exit, about, shift, clutch};

    int heading = 0;
    int task = 0;

    void encoderReceived(int value);
    void buttonPressReceived();

    void shiftValuesReceived(int a, int b, int c, int d);
    void clutchValuesReceived(int a, int b, int c, int d);
    void autoLaunchReceived(int );

    void sendShiftValues(int a, int b, int c, int d);
    void sendClutchValues(int a, int b, int c);
    void sendClutchPosition(int a);
    void sendDisableClutchOverride();
    void sendAutoLaunch(int state);
};

#endif // NAVIGATION_H
