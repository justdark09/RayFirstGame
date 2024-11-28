#include <iostream>
#include "raylib.h"

int main()
{
    constexpr int winHeight = 900;
    constexpr int winWidth = 1600;
    InitWindow(winWidth,winHeight,"Platformer");

    Texture2D knightIdle = LoadTexture("assets/sprites/FreeKnight_v1/Colour2/Outline/120x80_PNGSheets/_Idle.png");

    float frameWidth = static_cast<float>(knightIdle.width / 10.0);
    int maxFrames = knightIdle.width / static_cast<int>(frameWidth);

    float timer = 0.0f;
    int frame = 0;


    while (!WindowShouldClose()) {
        BeginDrawing();

        timer += GetFrameTime();

        if (timer >= 0.2f) {
            timer = 0.0f;
            frame += 1;
        }

        frame = frame % maxFrames;
        std::cout<<frame<<std::endl;

        DrawTextureRec(
            knightIdle,
            Rectangle{ frameWidth*frame, 0, frameWidth, (float)knightIdle.height},
            Vector2{ 0, 0 },
            WHITE);


        EndDrawing();
    }
    return 0;
}
