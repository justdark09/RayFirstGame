#include <iostream>

#include "knight.h"
#include "raylib.h"

int main()
{
    constexpr float winHeight = 900;
    constexpr float winWidth = 1600;
    InitWindow(winWidth,winHeight,"Platformer");
    SetTargetFPS(60);

    //Texture2D knightIdle = LoadTexture("assets/sprites/FreeKnight_v1/Colour2/Outline/120x80_PNGSheets/_IdleH.png");
    Texture2D knightIdle = LoadTexture("assets/sprites/FreeKnight_v1/Colour2/Outline/120x80_PNGSheets/_IdleH.png");
    Texture2D knightAttack2 = LoadTexture("assets/sprites/FreeKnight_v1/Colour2/NoOutline/120x80_PNGSheets/_Attack2H.png");

    const int knightScaleFactor = 5;

    const auto idleFrameWidth = static_cast<float>(knightIdle.width / 10.0);
    const int maxIdleFrames = knightIdle.width / static_cast<int>(idleFrameWidth);

    const auto attack2FrameWidth = static_cast<float>(knightAttack2.width / 10.0);
    const int maxAttack2Frames = knightAttack2.width / static_cast<int>(attack2FrameWidth);

    const float knightHeightScaled = knightIdle.height * knightScaleFactor;
    const float knightWidthScaled = idleFrameWidth * knightScaleFactor;

    float timer = 0.0f;
    int frame = 0;




    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(PURPLE);

        timer += GetFrameTime();

        if (timer >= 0.1f) {
            timer = 0.0f;
            frame += 1;
        }

        frame = frame % maxIdleFrames;
        //std::cout<<frame<<std::endl;

        DrawLine(0,winHeight/2,winWidth,winHeight/2, RED);
        DrawLine(winWidth/2,0,winWidth/2, winHeight, RED);
        DrawText("(800,450)", 800,450, 35, WHITE);




        const Rectangle source = { (idleFrameWidth*frame), 0, idleFrameWidth, static_cast<float>(knightIdle.height) };
        const Rectangle dest = { winWidth/2,winHeight/2, knightWidthScaled, knightHeightScaled };


        DrawTexturePro(knightIdle, source, dest, Vector2{ winWidth/2, winHeight/2}, 0, WHITE);

        DrawTexturePro(knightAttack2, source, dest, Vector2{ winWidth/2, winHeight/2}, 0, WHITE);




        EndDrawing();
    }
    UnloadTexture(knightIdle);
    UnloadTexture(knightAttack2);
    CloseWindow();
    return 0;
}
