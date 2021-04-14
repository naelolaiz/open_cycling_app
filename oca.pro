TEMPLATE = app
TARGET = oca

QT += qml quick bluetooth
CONFIG += c++11

HEADERS += \
    structs/CSCMeasurementData.h \
    structs/CyclingPowerMeasurementData.h \
    structs/FitnessMachineControlPoint.h \
    structs/FitnessMachineFeatureData.h \
    structs/IndoorBikeData.h \
    structs/VariousStructs.h \
    connectionhandler.h \
    deviceinfo.h \
    devicefinder.h \
    devicehandler.h \
    bluetoothbaseclass.h \
    oca-global.h

SOURCES += main.cpp \
    structs/CSCMeasurementData.cpp \
    structs/CyclingPowerMeasurementData.cpp \
    structs/FitnessMachineControlPoint.cpp \
    structs/FitnessMachineFeatureData.cpp \
    structs/IndoorBikeData.cpp \
    structs/VariousStructs.cpp \
    connectionhandler.cpp \
    deviceinfo.cpp \
    devicefinder.cpp \
    devicehandler.cpp \
    bluetoothbaseclass.cpp

RESOURCES += qml.qrc \
    images.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

target.path = $$[QT_INSTALL_EXAMPLES]/bluetooth/oca
INSTALLS += target
