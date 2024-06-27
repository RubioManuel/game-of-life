#include "raylib.h"

#include "grid.h"


int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Game of Life");
    SetTargetFPS(15);

    Grid *gameGrid = createGrid(400);
    randomizeGrid(gameGrid);


    while (!WindowShouldClose()) {

        BeginDrawing();

            ClearBackground(BLACK);
            drawGrid(gameGrid, screenWidth, screenHeight);

        EndDrawing();
        gameGrid = getNextFrameGrid(gameGrid);
    }

    freeGrid(gameGrid);
    CloseWindow();

    return 0;
}