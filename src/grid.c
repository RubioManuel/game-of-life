#include "raylib.h"

#include <stdlib.h>
#include <time.h>


typedef struct Grid {
    int gridSize;
    int **grid;
} Grid;


Grid *createGrid(int gridSize)
{
    Grid *newGrid = (Grid *) MemAlloc(sizeof(Grid));
    newGrid->gridSize = gridSize;

    int i;
    newGrid->grid = (int **) MemAlloc(sizeof(int *) * gridSize);

    for (i = 0; i < gridSize; i++) {
        newGrid->grid[i] = (int *) calloc(gridSize, sizeof(int));
    }

    return newGrid;
}

void randomizeGrid(Grid *grid)
{
    SetRandomSeed(time(NULL));
    int i, j;
    int prob;

    for (i = 0; i < grid->gridSize; i++) {
        for (j = 0; j < grid->gridSize; j++) {
            grid->grid[i][j] = GetRandomValue(0, 2);
        }
    }
}

void drawGrid(Grid *grid, int windowWidth, int windowHeight)
{
    int i, j;

    int cellWidth = windowWidth / grid->gridSize;
    int cellHeight = windowHeight / grid->gridSize;

    for (i = 0; i < grid->gridSize; i++) {
        for (j = 0; j < grid->gridSize; j++) {
            if (grid->grid[j][i] < 1) {
                Rectangle rect = {i * cellHeight, j * cellWidth, cellWidth, cellHeight};
                DrawRectangleLinesEx(rect, 0.5, BLACK);
            } else {
                DrawRectangle(i * cellHeight, j * cellWidth, cellWidth, cellHeight, RED);
            }
        }
    }
}

static bool nextCellState(int cellX, int cellY, int **grid, int gridSize)
{
    bool alive = grid[cellX][cellY];
    int aliveNeighbors = 0;

    if (cellX > 0 && cellY > 0 && grid[cellX - 1][cellY - 1]) {
        aliveNeighbors++;
    }

    if (cellX > 0 && grid[cellX - 1][cellY]) {
        aliveNeighbors++;
    }

    if (cellX > 0 && (cellY < gridSize - 1) && grid[cellX - 1][cellY + 1]) {
        aliveNeighbors++;
    }

    if ((cellY < gridSize - 1) && grid[cellX][cellY + 1]) {
        aliveNeighbors++;
    }

    if ((cellX < gridSize - 1) && (cellY < gridSize - 1) && grid[cellX + 1][cellY + 1]) {
        aliveNeighbors++;
    }

    if ((cellX < gridSize - 1) && grid[cellX + 1][cellY]) {
        aliveNeighbors++;
    }

    if ((cellX < gridSize - 1) && cellY > 0 && grid[cellX + 1][cellY - 1]) {
        aliveNeighbors++;
    }

    if (cellY > 0 && grid[cellX][cellY - 1]) {
        aliveNeighbors++;
    }

    if (alive && aliveNeighbors < 2) {
        return false;
    }

    if (alive && aliveNeighbors > 3) {
        return false;
    }

    if (alive && (aliveNeighbors == 2 || aliveNeighbors == 3)) {
        return true;
    }

    if (!alive && aliveNeighbors == 3) {
        return true;
    }

    return false;
}

Grid *getNextFrameGrid(Grid *currentGameGrid)
{
    void freeGrid(Grid *grid);

    Grid *nextFrameGrid = createGrid(currentGameGrid->gridSize);
    nextFrameGrid->gridSize = currentGameGrid->gridSize;

    int i, j;

    for (i = 0; i < currentGameGrid->gridSize; i++) {
        for (j = 0; j < currentGameGrid->gridSize; j++) {
            nextFrameGrid->grid[i][j] = currentGameGrid->grid[i][j];
        }
    }

    for (i = 0; i < currentGameGrid->gridSize; i++) {
        for (j = 0; j < currentGameGrid->gridSize; j++) {
            nextFrameGrid->grid[i][j] = nextCellState(i, j, currentGameGrid->grid, currentGameGrid->gridSize);
        }
    }
    
    /* Avoiding memory leaks freeing the memory used for the current game grid when
        computed the next grid state */
    freeGrid(currentGameGrid);

    return nextFrameGrid;
}

void freeGrid(Grid *grid)
{
    int i;

    for (i = 0; i < grid->gridSize; i++) {
        free(grid->grid[i]);
        grid->grid[i] = NULL;       /* Ensuring we are not freeing the memory twice */
    }
    free(grid);
    grid = NULL;
}