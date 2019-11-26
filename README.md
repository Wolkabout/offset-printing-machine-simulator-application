# Offset Printing Machine HMI, with Modbus TCP

This is an HMI QT application. This application is simulating the workings of an offset printing machine in HMI format,
and exposes its data through Modbus registers (specifically, Modbus TCP).

## Building & Installation

Clone this repository, and don't forget to add the  ```--recurse-submodules``` flag.
Otherwise you're not going to pull the library, which is necessary for the 
application to work.

### Dependencies

There is a shortcut for this, you can just run my shell script
```
. dependencies.sh
```

Or do this,
dependencies are QT 4, and to install that, you need
```
sudo apt install libqt4-dev libqt4-dev-bin \
                 libpthread-stubs0-dev \
                 libmodbus-dev
```

### Compile & Run

For this, there is also a shortcut. In the root of the git, run
```
. build.sh
(this will move you to /modbus-application-cpp/modbus-application/out/)
```

and then you need to run the app
```
./modbus-application
```

### Autostart

Create a xdg autostart entry by copying [modbus-application.desktop](modbus-application.desktop) into */etc/xdg/autostart/*
If you don't want application to start on boot, set
```
X-GNOME-Autostart-enabled=false
```

### How it works

Mostly, there are a few UI elements, that have defined listeners for machine components,
and they receive the data. Next to it, inputs to the machine are also taken through UI 
elements. Libmodbus is handling modbus things, and they run in a second thread,
where messages that are meant to change states of machine are interpreted and handled.
