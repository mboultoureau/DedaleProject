# SRC = src/*.cpp
SRC = $(shell find src/ -name "*.cpp")
CC = g++
FLAGS = -Wall -Wextra -g
LINKER = -lSDL2 -lSDL2_image -lSDL2_ttf -lopenal -lsndfile -lGLEW
OUT = build/BlindMaze

compile:
	mkdir -p build
	$(CC) $(FLAGS) $(SRC) $(LINKER) -o $(OUT) ; echo "./$(OUT)"
	