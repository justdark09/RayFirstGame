#include <iostream>
#include "raylib.h"

int main()
{
    InitWindow(1600, 900, "Knight Game");
    SetTargetFPS(60);

    Texture2D knightSheet = LoadTexture("assets/sprites/knight_sheet.png");
    const float frameHeight = knightSheet.height/30;
    float frameWidth = knightSheet.width/12;

    // holds the source Rectangle and the MaxFrames for each object of a texture
    struct AnimationStruct {
        Rectangle animRec;
        int maxFrames;
    };


    // make structs to hold each animation's values.
    // (i.e. where to get the src rectangle from, the max amount of frames that animatiion has, etc.)
    AnimationStruct idle_struct{};

    AnimationStruct attack_struct{};

    float timer = 0.0f;
    int frame = 0;
    int frame1 = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        timer += GetFrameTime();

        // increases the frame value every frameTime (tf does that actually mean)
        if (timer > .25f) {
            timer = 0.0f;
            frame += 1;
            frame1 += 1;
        }


        // initialize the animation structs
        idle_struct.maxFrames = 10;
        idle_struct.animRec = { frameWidth*frame, frameHeight*16, frameWidth, frameHeight };

        attack_struct.maxFrames = 4;
        attack_struct.animRec = { frameWidth*frame1, frameHeight, frameWidth, frameHeight };

        int currentMaxFrames = idle_struct.maxFrames;

        int tempMaxFrames = attack_struct.maxFrames;

        frame = frame % currentMaxFrames;
        frame1 = frame1 % tempMaxFrames;

        DrawTexturePro(
            knightSheet,
            idle_struct.animRec,
            Rectangle{ 800, 450, frameWidth*5, frameHeight*5},
            Vector2{0,0},
            0.f,
            WHITE);

        DrawTexturePro(
            knightSheet,
            attack_struct.animRec,
            Rectangle{ 400, 450, frameWidth*5, frameHeight*5},
            Vector2{0,0},
            0.f,
            WHITE);

        EndDrawing();
    }
    UnloadTexture(knightSheet);
    return 0;
}