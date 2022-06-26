#!/usr/bin/make

CC = gcc
BIN = ./bin
SRC = $(shell find ./ -name "*.c")
incl = $(shell find ./ -name "*.h")
OBJ = $(SRC:%.c=%.o)
prom = brain-fuck
INDIR = /usr/local/$(prom)
RESDIR = ./res

all: $(prom)

$(prom): $(OBJ)
	@rm -rf $(BIN)
	$(CC) -z now $(OBJ) -o $(prom)
	@mkdir bin
	@mv $(prom) $(BIN)/main

%.o: %.c $(incl)
	$(CC) -g -c $< -o $@

clean:
	@rm -rf $(OBJ)

