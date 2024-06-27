#if !defined(GRID_H)
#define GRID_H

#include <stdlib.h>

typedef struct Grid {
    int gridSize;
    int **grid;
} Grid;

Grid *createGrid(int gridSize);
void drawGrid(Grid *grid, int windowWidth, int windowHeight);
void randomizeGrid(Grid *grid);
Grid *getNextFrameGrid(Grid *currentGameGrid);
void freeGrid(Grid *grid);

#endif