mkdir out
pushd out
qmake-qt4 ../modbus-application.pro -r
make
sudo setcap CAP_NET_BIND_SERVICE=+eip ./modbus-application
popd
