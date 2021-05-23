#!/bin/sh
clear
if [ `dpkg --get-selections | grep brain-fuck |wc -l` -eq 1 ]
then
	clear
	sudo dpkg -r brain-fuck
fi
sudo dpkg -i ./build/brain-fuck.deb
rm ./build/brain-fuck.deb

