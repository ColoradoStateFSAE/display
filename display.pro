QT += core quick widgets qml serialbus

QTPLUGIN.platforms += qeglfs

LIBS += -L$$[QT_SYSROOT]/usr/lib -li2c -lws2811
LIBS += -L/usr/local/buildroot/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/lib -li2c

QMAKE_CXXFLAGS += -Wno-unused-variable
QMAKE_CXXFLAGS += -Wno-missing-field-initializers
QMAKE_CXXFLAGS += -Wno-unused-function

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/Encoder.cpp \
    Model/Motion.cpp \
    Model/NeoPixel.cpp \
    Navigation/Navigation.cpp \
    Util/canutil.cpp \
    ViewModel/ViewModel.cpp \
    main.cpp

RESOURCES += \
    resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /root
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Model/Encoder.h \
    Model/Gps.h \
    Model/Motion.h \
    Model/NeoPixel.h \
    Navigation/MenuItem.h \
    Navigation/Navigation.h \
    Util/canutil.h \
    ViewModel/ViewModel.h
