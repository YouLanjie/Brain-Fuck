#!/bin/sh
clear
cp -r ./src ./build/deb/brain-fuck/usr/local/brain-fuck/
dpkg -b ./build/deb/brain-fuck ./build/brain-fuck.deb
