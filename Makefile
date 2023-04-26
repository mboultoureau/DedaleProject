SRC = src/*.cpp
CC = g++
FLAGS = -Wall -Wextra -g
LINKER = -lSDL2 -lSDL2_image -lopenal
OUT = build/BlindMaze

compile:
	mkdir -p build
	$(CC) $(FLAGS) $(SRC) $(LINKER) -o $(OUT) ; echo "./$(OUT)"
	