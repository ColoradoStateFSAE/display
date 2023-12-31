#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QTimer>
#include <fstream>
#include <filesystem>
#include <QDateTime>

#include "Navigation/Navigation.h"
#include "Model/NeoPixel.h"
#include "Model/Gps.h"
#include "Model/Motion.h"

class ViewModel : public QObject {
    Q_OBJECT
public:
    ViewModel(Navigation &navigation, QObject *parent = nullptr) : QObject(parent), navigation(navigation) {
        time.start();
        lastShiftingSystemReceived = time.elapsed();
        lastEcuReceived = time.elapsed();

        filename = get_filename();

        // CAN
        QString errorString;
        device = QCanBus::instance()->createDevice(QStringLiteral("socketcan"), QStringLiteral("can0"), &errorString);
        device->setConfigurationParameter(QCanBusDevice::BitRateKey, QVariant());
        device->connectDevice();
        QObject::connect(device, &QCanBusDevice::framesReceived, this, &ViewModel::frameReceived);

        // NeoPixel
        NeoPixel *neoPixel = new NeoPixel(7500, 10000);
        QObject::connect(&neoPixelThread, &QThread::started, neoPixel, &NeoPixel::start);
        neoPixel->moveToThread(&neoPixelThread);
        neoPixelThread.start();

        QObject::connect(this, &ViewModel::rpmChanged, neoPixel, &NeoPixel::rpmReceived);
        QObject::connect(this, &ViewModel::batteryChanged, neoPixel, &NeoPixel::batteryReceived);
        QObject::connect(this, &ViewModel::coolantChanged, neoPixel, &NeoPixel::coolantReceived);
        QObject::connect(this, &ViewModel::sparkCutReceived, neoPixel, &NeoPixel::sparkCutReceived);

        gps = new Gps(get_filename());

        // Motion
        Motion *motion = new Motion(filename);
        QObject::connect(&motionThread, &QThread::started, motion, &Motion::start);
        motion->moveToThread(&motionThread);
        motionThread.start();

        // Update the screen every 17 ms
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, [this]() {
            // Do not update if the task switcher is active
            if(this->navigation.taskSwitcher) {
                return;
            }

            if(time.elapsed() - lastShiftingSystemReceived > 1000) {
                emit shiftingSystemOffline(true);
            } else {
                emit shiftingSystemOffline(false);
            }

            if(time.elapsed() - lastEcuReceived > 1000) {
                emit ecuOffline(true);
                emit batteryChanged(14);
            } else {
                emit ecuOffline(false);
                emit gearChanged(gear);
                emit rpmChanged(rpm);
                emit advanceChanged(advance);
                emit coolantChanged(coolant);
                emit tpsChanged(tps);
                emit batteryChanged(battery);
                emit afrChanged(afr);
                emit syncChanged(sync);
            }
        });
        timer->start(17);
    }

    ~ViewModel() {
        delete gps;
    }

signals:
    void gearChanged(int value);
    void rpmChanged(int value);
    void batteryChanged(float value);
    void coolantChanged(float value);
    void tpsChanged(float value);
    void afrChanged(float value);
    void syncChanged(float value);
    void advanceChanged(float value);
    void sparkCutReceived();
    void ecuOffline(bool state);
    void shiftingSystemOffline(bool state);

public slots:
    void frameReceived();

private:
    QElapsedTimer time;
    qint64 lastEcuReceived;
    qint64 lastShiftingSystemReceived;

    std::string filename;
    std::ofstream canFile;

    Navigation &navigation;
    QCanBusDevice *device;
    Gps *gps;

    QThread neoPixelThread;
    QThread motionThread;

    QTimer timer;

    int gear = 0;
    float rpm = 0;
    float battery = 0;
    float coolant = 0;
    float tps = 0;
    float afr = 0;
    float sync = 0;
    float advance = 0;

    std::string get_filename();

    void parseSpark(QByteArray data);
    void parseGear(QByteArray data);
    void parseGroup0(QByteArray data);
    void parseGroup1(QByteArray data);
    void parseGroup2(QByteArray data);
    void parseGroup3(QByteArray data);
    void parseGroup31(QByteArray data);
    void parseGroup43(QByteArray data);
};

#endif // VIEWMODEL_H
