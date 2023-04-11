SRC = src/*.cpp
CC = g++
FLAGS = -Wall -Wextra
LINKER = -lSDL2 -lSDL2_image
OUT = BlindMaze

compile:
	$(CC) $(FLAGS) $(SRC) $(LINKER) -o $(OUT)