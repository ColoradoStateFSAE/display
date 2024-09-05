#!/bin/bash

clear
set -e

mkdir -p build

/opt/qt5/bin/qmake -makefile display.pro
make -j$(nproc)
cd build
/opt/buildroot/output/host/arm-buildroot-linux-gnueabihf/bin/strip display

if test -e display; then
	rsync -Ph -e "ssh -i ~/.ssh/qtc_id" -avz display root@192.168.1.1:/root
	clear
	ssh -i ~/.ssh/qtc_id root@192.168.1.1 \
		"killall -9 display || true &&
		killall -9 /root/display || true &&
		clear &&
		/root/display;"
fi
