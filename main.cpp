#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSurfaceFormat>
#include <QQmlContext>

#include "ViewModel/ViewModel.h"
#include "Navigation/Navigation.h"

using namespace std;

void configure_environment() {
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

void device_properties(QQmlApplicationEngine &engine) {
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

    engine.rootContext()->setContextProperty("DEVICE", device);
    engine.rootContext()->setContextProperty("PROCESSOR", processor);
    engine.rootContext()->setContextProperty("MEMORY", memory);
    engine.rootContext()->setContextProperty("DISPLAY", display);
}

int main(int argc, char *argv[]) {
    configure_environment();

    QGuiApplication app(argc, argv);

    Navigation navigation;
    ViewModel viewModel(navigation);

    QQmlApplicationEngine engine;
    device_properties(engine);
    engine.rootContext()->setContextProperty(QStringLiteral("viewModel"), &viewModel);
    engine.rootContext()->setContextProperty(QStringLiteral("navigation"), &navigation);

    const QUrl url(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
