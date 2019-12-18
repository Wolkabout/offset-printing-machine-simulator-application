#-------------------------------------------------
#
# Project created by QtCreator 2019-09-13T11:46:33
#
#-------------------------------------------------

QT       += core gui network widgets svg
LIBS     += -lmodbus -pthread

lessThan(QT_MAJOR_VERSION, 4): error("requires Qt 4")
greaterThan(QT_MAJOR_VERSION, 4)
greaterThan(QT_MAJOR_VERSION, 5): error("requires Qt 4")

TARGET = modbus-application
TEMPLATE = app

QMAKE_CXXFLAGS += -std=gnu++17 -pthread
QMAKE_CXXFLAGS += -Wall -Wextra -pedantic
QMAKE_CXXFLAGS += -pedantic-errors -Wcast-align -Wcast-qual -Wconversion
QMAKE_CXXFLAGS += -Wdisabled-optimization -Wfloat-equal -Wformat=2
QMAKE_CXXFLAGS += -Werror=init-self -Werror=return-type -Werror=missing-field-initializers
QMAKE_CXXFLAGS += -Wmissing-format-attribute -Wmissing-include-dirs
QMAKE_CXXFLAGS += -Wmissing-noreturn -Werror=pointer-arith -Wno-packed  -Wno-padded
QMAKE_CXXFLAGS += -Wredundant-decls -Werror=shadow -Werror=stack-protector                                     \
QMAKE_CXXFLAGS += -Wstrict-aliasing=2 -Werror=unreachable-code -Wno-unused -Wvariadic-macros
QMAKE_CXXFLAGS += -Wwrite-strings -Werror=non-virtual-dtor

QMAKE_CFLAGS += -std=gnu++17 -pthread

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17 thread
UI_DIR = $$PWD

SOURCES += \
        Logs/alarmalert.cpp \
        Settings/configurations.cpp \
        Machine/conveyorcontrol.cpp \
        Machine/countlistener.cpp \
        Machine/deliverycontrol.cpp \
        Machine/feedercontrol.cpp \
        Logs/logs.cpp \
        Machine/machineview.cpp \
        main.cpp \
        mainwindow.cpp \
        Settings/messagealert.cpp \
        Modbus/modbusthread.cpp \
        Modbus/modbusthread_listeners.cpp \
        Modbus/modbusthreadmessagehandler.cpp \
        Machine/paintstationcontrol.cpp \
        Machine/ratelistener.cpp \
        Settings/settings.cpp \
        simulator.cpp \
        Machine/valueinput.cpp \
        windowmanager.cpp

HEADERS += \
        Logs/alarmalert.h \
        Modbus/bittogglethread.h \
        Settings/configurations.h \
        Machine/conveyorcontrol.h \
        Machine/countlistener.h \
        Machine/deliverycontrol.h \
        Machine/feedercontrol.h \
        Logs/logs.h \
        Machine/machineview.h \
        mainwindow.h \
        Settings/messagealert.h \
        Modbus/modbusthread.h \
        Modbus/modbusthread_listeners.h \
        Modbus/modbusthreadmessagehandler.h \
        Machine/paintstationcontrol.h \
        Machine/ratelistener.h \
        Settings/settings.h \
        simulator.h \
        utility.h \
        Machine/valueinput.h \
        windowmanager.h

FORMS += \
        Logs/alarmalert.ui \
        Machine/conveyorcontrol.ui \
        Machine/deliverycontrol.ui \
        Machine/feedercontrol.ui \
        Logs/logs.ui \
        Machine/machineview.ui \
        mainwindow.ui \
        Settings/messagealert.ui \
        Machine/paintstationcontrol.ui \
        Settings/settings.ui \
        Machine/valueinput.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/../modbus-simulator-cpp/out/ -lmodbus_simulator_cpp

INCLUDEPATH += $$PWD/../modbus-simulator-cpp
DEPENDPATH += $$PWD/../modbus-simulator-cpp

unix:!macx: PRE_TARGETDEPS += $$PWD/../modbus-simulator-cpp/out/libmodbus_simulator_cpp.a

RESOURCES += \
    Resources/fonts.qrc \
    Resources/icons.qrc \
    Resources/images.qrc
