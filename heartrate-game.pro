TEMPLATE = app
TARGET = heartrate-game

QT += qml quick bluetooth
CONFIG += c++11

HEADERS += \
    CSCMeasurementData.h \
    CyclingPowerMeasurementData.h \
    IndoorBikeData.h \
    connectionhandler.h \
    deviceinfo.h \
    devicefinder.h \
    devicehandler.h \
    bluetoothbaseclass.h \
    heartrate-global.h

SOURCES += main.cpp \
    CSCMeasurementData.cpp \
    CyclingPowerMeasurementData.cpp \
    IndoorBikeData.cpp \
    connectionhandler.cpp \
    deviceinfo.cpp \
    devicefinder.cpp \
    devicehandler.cpp \
    bluetoothbaseclass.cpp

RESOURCES += qml.qrc \
    images.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

target.path = $$[QT_INSTALL_EXAMPLES]/bluetooth/heartrate-game
INSTALLS += target
