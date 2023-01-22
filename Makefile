#!/usr/bin/make

CC = gcc
BIN = ./bin
SRC = $(shell find ./ -name "*.c")
incl = $(shell find ./ -name "*.h")
OBJ = $(SRC:%.c=%.o)
prom = game-of-life
INDIR = /usr/local/$(prom)
RESDIR = ./res

all: game-of-life

$(prom): $(OBJ)
	@if [ ! -d "$(BIN)" ]; then mkdir $(BIN); fi
	$(CC) $(OBJ) -g -L lib -ltools -lncurses -o $(BIN)/main

%.o: %.c $(incl)
	$(CC) -g -c $< -o $@

clean:
	@rm -rf $(BIN) $(OBJ)

