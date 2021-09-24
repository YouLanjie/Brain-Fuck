#!/usr/bin/make

prom = brain-fuck

all: $(prom)

$(prom): 
	dpkg -b ./deb/$(prom) ./$(prom).deb

install:
	@sudo dpkg -i ./$(prom).deb
	@rm ./$(prom).deb


