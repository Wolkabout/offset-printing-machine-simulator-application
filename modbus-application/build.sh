mkdir out
cd out
qmake-qt4 ../modbus-application.pro -r CONFIG+=debug
make
sudo setcap CAP_NET_BIND_SERVICE=+eip ./modbus-application
