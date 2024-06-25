# Compilation of Game of Life (gol.c file).
# Basic compilation instruction for a raylib program using gcc
gol: ./src/gol.c
	gcc ./src/gol.c -o ./bin/gol -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# All binary files go to `bin` directory.
clean:
	rm ./bin/*
