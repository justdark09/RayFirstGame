#include <iostream>
#include "raylib.h"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

int printThanks()
{
    std::cout<<"\nThanks for PlayTesting!\n";
    return 0;
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Knight Game");
    SetTargetFPS(60);

    Texture2D knightSheet = LoadTexture("assets/sprites/knight_sheet.png");
    const float frameHeight = static_cast<float>(knightSheet.height)/30;
    const float frameWidth = static_cast<float>(knightSheet.width)/12;
    const float flippedFrame = -frameWidth;
    float currentFrame = frameWidth;

    // holds the source Rectangle and the MaxFrames for each object of a texture
    struct AnimationStruct {
        float animationHeight;
        int maxFrames;
    };

    // make structs to hold each animation's values.
    // (i.e. where to get the src rectangle from, the max amount of frames that animation has, etc.)
    AnimationStruct attack1_struct{};
    AnimationStruct attack2_struct{};
    AnimationStruct run_struct{};
    AnimationStruct idle_struct{};
    AnimationStruct crouch_struct{};

    // placeholder struct so the textures can be changed
    AnimationStruct current_struct{};

    int currentMaxFrames;

    float timer = 0.0f;
    int frame = 0;

    float spriteX = 0;
    float spriteY = 0;

    std::cout<<spriteX<<", "<<spriteY<<std::endl;
    std::cout<<frameWidth<<", "<<frameHeight<<std::endl;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        timer += GetFrameTime();

        // increases the frame value every frameTime (tf does that actually mean)
        if (timer > .12f) {
            timer = 0.0f;
            frame += 1;
        }


        // initialize the animation structs
        // !! maxFrames should equal the number of frames the animation has MINUS ONE !!
        idle_struct.maxFrames = 9;
        idle_struct.animationHeight = frameHeight*16.f;

        attack2_struct.maxFrames = 5;
        attack2_struct.animationHeight = frameHeight*2.f;

        attack1_struct.maxFrames = 3;
        attack1_struct.animationHeight = (float)frameHeight;

        run_struct.maxFrames = 9;
        run_struct.animationHeight = frameHeight*20.f;

        crouch_struct.maxFrames = 3;
        crouch_struct.animationHeight = frameHeight*7;

        const float runMultiplier = 1.25;
        const float crouchMultiplier = .5;



        if (IsKeyDown(KEY_D)) {
            currentFrame = frameWidth;

            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                spriteX += 5 * runMultiplier;
            }

            if (IsKeyDown(KEY_S)) {
                spriteX += 5 * crouchMultiplier;
                current_struct = crouch_struct;
            } else {
                spriteX += 5;
                current_struct = run_struct;
            }

        } else if (IsKeyDown(KEY_A)) {
            currentFrame = flippedFrame;

            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                spriteX -= 5 * runMultiplier;
            }

            if (IsKeyDown(KEY_S)) {
                spriteX -= 5 * crouchMultiplier;
                current_struct = crouch_struct;
            } else {
                spriteX -= 5;
                current_struct = run_struct;
                currentFrame = flippedFrame;
            }

        } else {
            current_struct = idle_struct;
        }




        currentMaxFrames = current_struct.maxFrames;

        frame = frame % currentMaxFrames;


        DrawTexturePro(
            knightSheet,
            Rectangle{ frameWidth*frame, current_struct.animationHeight, currentFrame, frameHeight },
            Rectangle{ spriteX+(frameWidth*5),spriteY+(frameHeight*5), frameWidth*5, frameHeight*5 },
            Vector2{0,0},
            0.f,
            WHITE);

            // todo: spriteX and spriteY do not work with SCREEN_HEIGHT or SCREEN_WIDTH
            //  causing the sprite to not be drawn on the screen in the first place

        EndDrawing();

    }
    UnloadTexture(knightSheet);
    printThanks();
    return 0;
}