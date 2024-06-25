#include "raylib.h"


int main(void)
{
    InitWindow(800, 450, "Hello World with Raylib");

    while (!WindowShouldClose()) {

        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Hello, world!", 280, 200, 40, WHITE);
        EndDrawing();
    }

    return 0;
}