#-------------------------------------------------
#
# Project created by QtCreator 2019-09-13T11:46:33
#
#-------------------------------------------------

QT       += core gui network widgets svg
LIBS     += -pthread

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
QMAKE_CXXFLAGS += -Wmissing-noreturn -Werror=pointer-arith -Wno-packed -Wno-padded
QMAKE_CXXFLAGS += -Wredundant-decls -Werror=shadow -Werror=stack-protector
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
        logs/AlarmAlert.cpp \
        logs/Logs.cpp \
        machine/ConveyorControl.cpp \
        machine/CountListener.cpp \
        machine/DeliveryControl.cpp \
        machine/FeederControl.cpp \
        machine/MachineView.cpp \
        machine/PaintStationControl.cpp \
        machine/RateListener.cpp \
        machine/ValueInput.cpp \
        external/ModbusThread.cpp \
        external/ModbusThreadListeners.cpp \
        external/ModbusThreadMessageHandler.cpp \
        settings/Configurations.cpp \
        settings/MessageAlert.cpp \
        settings/Settings.cpp \
        Main.cpp \
        MainWindow.cpp \
        Simulator.cpp \
        WindowManager.cpp

HEADERS += \
        logs/AlarmAlert.h \
        logs/Logs.h \
        machine/ConveyorControl.h \
        machine/CountListener.h \
        machine/DeliveryControl.h \
        machine/FeederControl.h \
        machine/MachineView.h \
        machine/PaintStationControl.h \
        machine/RateListener.h \
        machine/ValueInput.h \
        external/BitToggleThread.h \
        external/ModbusThread.h \
        external/ModbusThreadListeners.h \
        external/ModbusThreadMessageHandler.h \
        settings/Configurations.h \
        settings/MessageAlert.h \
        settings/Settings.h \
        MainWindow.h \
        Simulator.h \
        Utility.h \
        WindowManager.h

FORMS += \
        logs/AlarmAlert.ui \
        logs/Logs.ui \
        machine/ConveyorControl.ui \
        machine/DeliveryControl.ui \
        machine/FeederControl.ui \
        machine/MachineView.ui \
        machine/PaintStationControl.ui \
        machine/ValueInput.ui \
        settings/MessageAlert.ui \
        settings/Settings.ui \
        MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/binunix: LIBS += -L$$PWD/../offset-printing-machine-simulator-lib/out/ -lopm-simulator

INCLUDEPATH += $$PWD/../offset-printing-machine-simulator-lib/src
DEPENDPATH += $$PWD/../offset-printing-machine-simulator-lib/src

unix: PRE_TARGETDEPS += $$PWD/../offset-printing-machine-simulator-lib/out/libopm-simulator.a
!isEmpty(target.path): INSTALLS += target

unix: LIBS += -L$$PWD/../offset-printing-machine-simulator-lib/out/ -lopm-simulator
unix: LIBS += -L$$PWD/../dependencies/out/lib/ -lmodbus

INCLUDEPATH += $$PWD/../dependencies/include
DEPENDPATH += $$PWD/../dependencies/include

unix: PRE_TARGETDEPS += $$PWD/../dependencies/out/lib/libmodbus.a

RESOURCES += \
    resources/fonts.qrc \
    resources/icons.qrc \
    resources/images.qrc
