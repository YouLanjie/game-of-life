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
	@rm -rf $(BIN)
	@mkdir bin
	$(CC) $(OBJ) -g -L lib -ltools -o $(BIN)/main

%.o: %.c $(incl)
	$(CC) -g -c $< -o $@

clean:
	@rm -rf $(OBJ)

