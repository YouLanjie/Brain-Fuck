#!/bin/bash

rm -r ./deb/brain-fuck/usr/local/brain-fuck/*
cp -r ./src ./deb/brain-fuck/usr/local/brain-fuck/
cp -r ./include ./deb/brain-fuck/usr/local/brain-fuck/
dpkg -b ./deb/brain-fuck ./deb/brain-fuck.deb
if [ `dpkg --get-selections brain-fuck |wc -l` -eq 1 ]
then
	sudo dpkg -r brain-fuck
fi
sudo dpkg -i ./deb/brain-fuck.deb
rm ./deb/brain-fuck.deb

