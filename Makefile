SRC = src/*.cpp
CC = g++
FLAGS = -Wall -Wextra
LINKER = -lSDL2 -lSDL2_image
OUT = build/BlindMaze

compile:
	mkdir -p build
	$(CC) $(FLAGS) $(SRC) $(LINKER) -o $(OUT)