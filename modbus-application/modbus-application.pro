#-------------------------------------------------
#
# Project created by QtCreator 2019-09-13T11:46:33
#
#-------------------------------------------------

QT       += core gui
LIBS     += -lmodbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = modbus-application
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
UI_DIR = $$PWD

SOURCES += \
        logs.cpp \
        machineview.cpp \
        main.cpp \
        mainwindow.cpp \
        settings.cpp \
        simulator.cpp \
        windowmanager.cpp

HEADERS += \
        logs.h \
        machineview.h \
        mainwindow.h \
        settings.h \
        simulator.h \
        windowmanager.h

FORMS += \
        logs.ui \
        machineview.ui \
        mainwindow.ui \
        settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/../modbus-simulator-cpp/out/ -lmodbus_simulator_cpp

INCLUDEPATH += $$PWD/../modbus-simulator-cpp
DEPENDPATH += $$PWD/../modbus-simulator-cpp

unix:!macx: PRE_TARGETDEPS += $$PWD/../modbus-simulator-cpp/out/libmodbus_simulator_cpp.a

RESOURCES += \
    animations.qrc

DISTFILES += \
    Resources/ConveyorAnimation1.gif \
    Resources/ConveyorAnimation2.gif \
    Resources/DeliveryAnimation1.gif \
    Resources/DeliveryAnimation2.gif \
    Resources/FeederAnimation1.gif \
    Resources/FeederAnimation2.gif \
    Resources/PaintStationAnimationC1.gif \
    Resources/PaintStationAnimationC2.gif \
    Resources/PaintStationAnimationK1.gif \
    Resources/PaintStationAnimationK2.gif \
    Resources/PaintStationAnimationM1.gif \
    Resources/PaintStationAnimationM2.gif \
    Resources/PaintStationAnimationY1.gif \
    Resources/PaintStationAnimationY2.gif
