#-------------------------------------------------
#
# Project created by QtCreator 2019-09-13T11:46:33
#
#-------------------------------------------------

QT       += core gui

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

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../modbus-simulator-cpp/out/release/ -lmodbus_simulator_cpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../modbus-simulator-cpp/out/debug/ -lmodbus_simulator_cpp
else:unix: LIBS += -L$$PWD/../modbus-simulator-cpp/out/ -lmodbus_simulator_cpp

INCLUDEPATH += $$PWD/../modbus-simulator-cpp/out
DEPENDPATH += $$PWD/../modbus-simulator-cpp/out

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../modbus-simulator-cpp/out/release/libmodbus_simulator_cpp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../modbus-simulator-cpp/out/debug/libmodbus_simulator_cpp.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../modbus-simulator-cpp/out/release/modbus_simulator_cpp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../modbus-simulator-cpp/out/debug/modbus_simulator_cpp.lib
else:unix: PRE_TARGETDEPS += $$PWD/../modbus-simulator-cpp/out/libmodbus_simulator_cpp.a
