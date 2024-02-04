#!/usr/bin/make

SRC = $(shell find ./ -name "*.c")
incl = $(shell find ./ -name "*.h")
OBJ = $(SRC:%.c=%.o)
BIN = ./bin

all: build

.PHONY: build
build: $(OBJ)
	@if [ ! -d "$(BIN)" ]; then mkdir $(BIN); fi
	$(CC) -z now $(OBJ) -lncurses -o $(BIN)/main

%.o: %.c $(incl)
	$(CC) -g -Wall -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ)

