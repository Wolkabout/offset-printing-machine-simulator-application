# Modbus TCP HMI

This is an HMI QT application, running on an IEI embedded machine with a IEI touch screen.
This application is simulating the workings of an offset printing machine, and is connected
to the platform with the Modbus protocol, over a [WolkGateway](https://github.com/wolkabout/WolkGateway) + [WolkGatewayModule-Modbus](https://github.com/wolkabout/WolkGatewayModule-Modbus).

## Installation

To clone this repository, run
```
git clone --recurse-submodules https://github.com/nexylmao/modbus-application-cpp
```

### Dependencies

There is a shortcut for this, you can just run my shell script
```
. dependencies.sh
```

Dependencies are QT 4, and to install that, you need
```
sudo apt install libqt4-dev libqt4-dev-bin
```
And that gives you everything necessary to qmake and run the application.

You need pthread
```
sudo apt install libpthread-stubs0-dev
```

... and you need libmodbus
```
sudo apt install libmodbus-dev
```

### Compile & Run

For this, there is also a shortcut. In the root of the git, run
```
. build.sh
```

You will be in the folder
```
.../modbus-application-cpp/modbus-application/out/
```

and then you need to run the app
```
./modbus-application
```

## Setting up with the gateway

Follow the guides from both the [WolkGateway](https://github.com/wolkabout/WolkGateway), and its [Modbus Module](https://github.com/wolkabout/WolkGatewayModule-Modbus).

After that, you need to configure Modbus. IP address of the HMI will be displayed in the settings part of the application, so you can type that in the config. 
!!! Set the port to 2222 !!!.
You need to use the .json file provided in this git, called modbusRegisterMapping.json, and place it in the out folder of the module, and run the module with that file.

Place the modbus-application.desktop file in the /etc/xdg/autostart/ folder.
Replace the [USER_NAME] part with your username/modify the path if that's necessary.

(In development)
The modbus module still doesn't support alarms, so you need to set them up in the rule engine of the platform.
