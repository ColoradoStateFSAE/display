QT += core gui quick widgets qml serialbus
QTPLUGIN.platforms += qeglfs

CONFIG += object_parallel_to_source
QMAKE_PROJECT_DEPTH = 0

QMAKE_CXXFLAGS += -Wno-unused-variable
QMAKE_CXXFLAGS += -Wno-missing-field-initializers
QMAKE_CXXFLAGS += -Wno-unused-function
QMAKE_CXXFLAGS += -Wfatal-errors

SOURCES += $$files(src/*.c, true) $$files(src/*.cpp, true)
HEADERS += $$files(src/*.h, true)
RESOURCES += res/resources.qrc

LIBS += -L$$[QT_SYSROOT]/usr/lib -li2c -lws2811

DESTDIR = $$PWD/build
OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR = $$DESTDIR/moc
RCC_DIR = $$DESTDIR/rcc
UI_DIR = $$DESTDIR/ui
