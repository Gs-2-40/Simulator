#include "raylib.h"
#include "raymath.h"
#include "src/config.h"

int main() {
    InitWindow(800, 600, "Simulator");
    SetTargetFPS(60);

    World* world;
    Subject* player = nullptr; // Изменили на указатель

    initconfig(world, player);
    
    world->world_transform = MatrixScale(scaleFactor, scaleFactor, scaleFactor);
    
    while (!WindowShouldClose()) {
        player->UpdateCamera();
        float time = GetTime();
        Matrix mat = MatrixIdentity();
        Vector2 mouseDelta = GetMouseDelta();

        world->process(timeScale);
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Входим в 3D режим
        BeginMode3D(player->camera);

            world->draw();
            DrawGrid(10, 1.0f); 

        EndMode3D();

        DrawText("Welcome to 3D World!", 10, 10, 20, DARKGRAY);
        DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}