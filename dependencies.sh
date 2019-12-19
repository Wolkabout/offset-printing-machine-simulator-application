sudo snap install cmake --classic
sudo apt install gcc g++ make libqt4-dev libqt4-dev-bin libpthread-stubs0-dev autoconf automake libtool

pushd dependencies
. download.sh
. make.sh
popd
