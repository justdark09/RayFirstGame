#include <iostream>
#include "raylib.h"


int main()
{
    constexpr float winHeight = 900;
    constexpr float winWidth = 1600;
    InitWindow(winWidth,winHeight,"Platformer");
    SetTargetFPS(60);

    Texture2D knightIdle = LoadTexture("assets/sprites/FreeKnight_v1/Colour2/NoOutline/120x80_PNGSheets/_IdleH.png");
    Texture2D knightAttack2 = LoadTexture("assets/sprites/FreeKnight_v1/Colour2/NoOutline/120x80_PNGSheets/_Attack2H.png");
    Texture2D knightAttackNoMove = LoadTexture("assets/sprites/FreeKnight_v1/Colour2/NoOutline/120x80_PNGSheets/_Attack2NoMovementH.png");


    Texture2D currentTexture = knightIdle;

    const int knightScaleFactor = 5;

    const auto currentTextureFrameWidth = static_cast<float>(currentTexture.width / 10.0);
    const int maxIdleFrames = knightIdle.width / static_cast<int>(currentTextureFrameWidth);


    /*
    const auto attack2FrameWidth = static_cast<float>(knightAttack2.width / 6.0);
    const int maxAttack2Frames = knightAttack2.width / static_cast<int>(attack2FrameWidth);

    const auto noMoveAttackFrameWidth = static_cast<float>(knightAttackNoMove.width / 6.0);
    const int maxNoMoveFrames = knightAttackNoMove.width / static_cast<int>(noMoveAttackFrameWidth);
    */


    const float knightHeightScaled = knightIdle.height * knightScaleFactor;
    const float knightWidthScaled = currentTextureFrameWidth * knightScaleFactor;


    float timer = 0.0f;
    int frameIdle = 0;
    int frameAtt = 0;
    int frameNoMove = 0;

    float idleStartPos = winWidth/2;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(PURPLE);

        timer += GetFrameTime();

        if (timer >= 0.1f) {
            timer = 0.0f;
            frameIdle += 1;
            frameAtt += 1;
            frameNoMove += 1;
        }

        frameIdle = frameIdle % maxIdleFrames;
        //frameAtt = frameAtt % maxAttack2Frames;
        //std::cout<<frame<<std::endl;

        DrawLine(0,winHeight/2,winWidth,winHeight/2, RED);
        DrawLine(winWidth/2,0,winWidth/2, winHeight, RED);



        if (IsKeyDown(KEY_D)) {
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                idleStartPos += GetFrameTime() * 300;
                currentTexture = knightAttackNoMove;
            } else {
                idleStartPos += GetFrameTime() * 100;
                currentTexture = knightIdle;
            }
        } else {
            currentTexture = knightIdle;
        }

        if (IsKeyDown(KEY_A)) {
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                idleStartPos -= GetFrameTime() * 300;
                currentTexture = knightAttackNoMove;
            } else {
                idleStartPos -= GetFrameTime() * 100;
                currentTexture = knightIdle;
            }
        } else {
            currentTexture = knightIdle;
        }

        DrawTexturePro(
            currentTexture,
            Rectangle{ (currentTextureFrameWidth*frameIdle), 0, currentTextureFrameWidth, static_cast<float>(knightIdle.height) },
            Rectangle{ idleStartPos,winHeight/2, knightWidthScaled, knightHeightScaled },
            Vector2{ currentTextureFrameWidth/2,static_cast<float>(knightIdle.height)/2}, 0, WHITE);

        /*
        DrawTexturePro(
            knightAttack2,
            Rectangle{ (attack2FrameWidth*frameAtt), 0, attack2FrameWidth, static_cast<float>(knightAttack2.height)},
            Rectangle{winWidth/4,winHeight/2, attack2FrameWidth*5, (float)knightAttack2.height*5},
            Vector2{ attack2FrameWidth/2,static_cast<float>(knightAttack2.height)/2}, 0, WHITE);

        DrawTexturePro(
            knightAttackNoMove,
            Rectangle{ noMoveAttackFrameWidth*frameNoMove, 0, noMoveAttackFrameWidth, static_cast<float>(knightAttackNoMove.height) },
            Rectangle{ winWidth-(winWidth/4),winHeight/2, noMoveAttackFrameWidth*5, (float)knightAttackNoMove.height*5},
            Vector2{ noMoveAttackFrameWidth/2, static_cast<float>(knightAttackNoMove.height)/2}, 0, WHITE);

        */

        EndDrawing();
    }
    UnloadTexture(knightIdle);
    UnloadTexture(knightAttack2);
    UnloadTexture(knightAttackNoMove);
    CloseWindow();
    return 0;
}
