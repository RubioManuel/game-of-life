# Compilation of Game of Life (gol.c file).
# Basic compilation instruction for a raylib program using gcc
gol: ./src/gol.c ./src/grid.c
	gcc ./src/gol.c ./src/grid.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o ./bin/gol

# All binary files go to `bin` directory.
clean:
	rm ./bin/*
