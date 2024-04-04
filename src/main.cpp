#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSurfaceFormat>
#include <QQmlContext>
#include <cmath>
#include <QtPlugin>
#include <iostream>
#include "ViewModel/ViewModel.h"
#include "Navigation/Navigation.h"
#include "Gps/Gps.h"
#include <QQuickWindow>
#include <QScreen>
#include <QImage>
#include <QPixmap>

using namespace std;

void configureEnvironment() {
	QSurfaceFormat format;
	format.setSamples(1);
	QSurfaceFormat::setDefaultFormat(format);

	qputenv("QT_QPA_PLATFORM", "eglfs");
	qputenv("QT_QPA_EGLFS_FORCE888", "1");
	qputenv("QT_QPA_EGLFS_PHYSICAL_WIDTH", "100");
	qputenv("QT_QPA_EGLFS_PHYSICAL_HEIGHT", "100");
	qputenv("XDG_RUNTIME_DIR", "/tmp/runtime-root");
	qputenv("QT_QPA_FONTDIR", "/usr/share/fonts");
}

void setDeviceProperties(QQmlApplicationEngine &engine) {
	QString device = "Device not found";
	QString processor = "placeholder";
	QString memory = "placeholder";
	QString display = "placeholder";

	std::ifstream file("/proc/device-tree/model");
	if (!file.is_open()) {
		qDebug() << "Could not open '/proc/device-tree/model'";
	}

	string line;
	getline(file, line);
	file.close();

	if (line.find("Raspberry Pi Zero 2 W") != string::npos) {
		device = "Raspberry Pi Zero 2 W";
		processor = "Raspberry Pi RP3A0";
		memory = "512 MB";
		display = "Matrix Orbital HTT50A-IPS";

	} else if(line.find("Raspberry Pi 3 Model A Plus") != string::npos) {
		device = "Raspberry Pi 3 Model A+";
		processor = "Broadcom BCM2837B0";
		memory = "512 MB";
		display = "Matrix Orbital HTT50A-IPS";

	} else if(line.find("Raspberry Pi 3 Model B Plus") != string::npos) {
		device = "Raspberry Pi 3 Model B+";
		processor = "Broadcom BCM2837B0";
		memory = "1 GB";
		display = "Matrix Orbital HTT50A-IPS";
	}

	engine.rootContext()->setContextProperty(QStringLiteral("DEVICE"), device);
	engine.rootContext()->setContextProperty(QStringLiteral("PROCESSOR"), processor);
	engine.rootContext()->setContextProperty(QStringLiteral("MEMORY"), memory);
	engine.rootContext()->setContextProperty(QStringLiteral("DISPLAY"), display);
}

QList<QCanBusDevice::Filter> filter() {
	QCanBusDevice::Filter filter;
	filter.type = QCanBusFrame::DataFrame;
	filter.format = QCanBusDevice::Filter::MatchBaseFormat;
	filter.frameIdMask = 0x7FF;

	QList<QCanBusDevice::Filter> filterList;

	for(unsigned i = R3_GROUP0_FRAME_ID; i <= R3_GROUP39_FRAME_ID; i++) {
        filter.frameId = i;
        filterList.append(filter);
    }

	for(unsigned i = TCS_GEAR_FRAME_ID; i <= TCS_ANALOG_INPUT_FRAME_ID; i++) {
        filter.frameId = i;
        filterList.append(filter);
    }

	filter.frameId = 0x6A4;
	filterList.append(filter);

	return filterList;
}

void screenshot(QQmlApplicationEngine &engine) {
	QTimer::singleShot(2000, [&](){
		foreach(QObject *obj, engine.rootObjects()) {
			QQuickWindow* window = qobject_cast<QQuickWindow*>(obj);
			if(window) {
				QImage image = window->grabWindow();
				image.save("/root/screenshot.png");
			}
		}
	});
}

int main(int argc, char *argv[]) {
	configureEnvironment();

	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;

	// CAN
	QString errorString;
	QCanBusDevice *device = QCanBus::instance()->createDevice(QStringLiteral("socketcan"), QStringLiteral("can0"), &errorString);
	device->setConfigurationParameter(QCanBusDevice::BitRateKey, QVariant());
	device->setConfigurationParameter(QCanBusDevice::RawFilterKey, QVariant::fromValue(filter()));
	device->connectDevice();

	Navigation navigation(device);
	ViewModel viewModel(navigation);

	QObject::connect(device, &QCanBusDevice::framesReceived, [&](){
		while(device->framesAvailable()) {
			const QCanBusFrame frame = device->readFrame();
			viewModel.frameReceived(frame);
			navigation.frameReceived(frame);

			if(frame.frameId() == 0x6A4) {
				cout << "Screenshot saved" << endl;
				screenshot(engine);
			}
		}
	});

	setDeviceProperties(engine);
	engine.rootContext()->setContextProperty(QStringLiteral("viewModel"), &viewModel);
	engine.rootContext()->setContextProperty(QStringLiteral("navigation"), &navigation);
	qmlRegisterType<Navigation>("navigation", 1, 0, "Navigation");

	const QUrl url(QUrl(QStringLiteral("qrc:/qml/main.qml")));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
		&app, [url](QObject *obj, const QUrl &objUrl) {
			if (!obj && url == objUrl)
				QCoreApplication::exit(-1);
		}, Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
