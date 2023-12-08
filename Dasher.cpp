#include "raylib.h"

struct AnimData
{

    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    //window dimensions

    int windowDimensions[2] = {512, 380};
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper");

    // scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Texture2D foreGround = LoadTexture("textures/foreground.png");
    Texture2D farBuilding = LoadTexture("textures/back-buildings.png");
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Texture2D backBuilding = LoadTexture("textures/far-buildings.png");

    // Scarfy
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    // nebula

    const int sizeOfNebilae = 3;
    AnimData nebulae[sizeOfNebilae]{};

    for (int i = 0; i < sizeOfNebilae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0 / 12.0;
        nebulae[i].pos.x = windowDimensions[0] += 300 * i;
    }

    // Back Grounds Positions
    Vector2 backPos{0.0, 0.0};
    Vector2 back2Pos{float(backBuilding.width * 2.0 + backPos.x), 0.0};

    Vector2 farPos{0.0, 0.0};
    Vector2 far2Pos{float(farBuilding.width * 2.0), 0.0};

    Vector2 forePos{0.0, 0.0};
    Vector2 fore2Pos{float(foreGround.width * 2.0), 0.0};

    // nebula update animation
    float finishLine{nebulae[sizeOfNebilae - 1].pos.x + 50};
    bool lost = {false};

    int nebVal = -200;

    int velocity = 0;
    int gravity = 1'000;
    bool isInAir{false};
    const int jumb = -600;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        //start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        if (backPos.x + backBuilding.width * 2 < 0)
        {
            backPos.x = back2Pos.x + backBuilding.width * 2;
        }
        if (back2Pos.x + backBuilding.width * 2 < 0)
        {
            back2Pos.x = backPos.x + backBuilding.width * 2;
        }
        if (farPos.x + farBuilding.width * 2 < 0)
        {
            farPos.x = far2Pos.x + farBuilding.width * 2;
        }
        if (far2Pos.x + farBuilding.width * 2 < 0)
        {
            far2Pos.x = farPos.x + farBuilding.width * 2;
        }

        if (forePos.x + foreGround.width * 2 < 0)
        {
            forePos.x = fore2Pos.x + foreGround.width * 2;
        }
        if (fore2Pos.x + foreGround.width * 2 < 0)
        {
            fore2Pos.x = forePos.x + foreGround.width * 2;
        }

        DrawTextureEx(backBuilding, backPos, 0.0, 2.0, WHITE);

        DrawTextureEx(backBuilding, back2Pos, 0.0, 2.0, WHITE);

        DrawTextureEx(farBuilding, farPos, 0.0, 2.0, WHITE);

        DrawTextureEx(farBuilding, far2Pos, 0.0, 2.0, WHITE);

        DrawTextureEx(foreGround, forePos, 0.0, 2.0, WHITE);
        DrawTextureEx(foreGround, fore2Pos, 0.0, 2.0, WHITE);

        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        for (int i = 0; i < sizeOfNebilae; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        const double dt = GetFrameTime();

        //Update position
        scarfyData.pos.y += velocity * dt;

        for (int i = 0; i < sizeOfNebilae; i++)
        {
            nebulae[i].pos.x += nebVal * dt;
        }
        backPos.x += -50 * dt;
        back2Pos.x += -50 * dt;
        farPos.x += -100 * dt;
        far2Pos.x += -100 * dt;
        forePos.x += -200 * dt;
        fore2Pos.x += -200 * dt;

        // Perform ground check
        if (scarfyData.pos.y >= windowDimensions[1] - scarfy.height)
        {

            scarfyData.pos.y = windowDimensions[1] - scarfy.height;
            velocity = 0;
            isInAir = false;
        }
        else // rec is in the air
        {

            isInAir = true;
            velocity += gravity * dt;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumb;
        }

        // update scarfy

        scarfyData.runningTime += dt;
        if (!isInAir)
        {

            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0.0;

                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if (scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
            }
        }

        {
        }

        // Update nebula

        for (int i = 0; i < sizeOfNebilae; i++)
        {

            nebulae[i].runningTime += dt;
            if (nebulae[i].runningTime >= nebulae[i].updateTime)
            {

                nebulae[i].runningTime = 0;
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;
                if (nebulae[i].frame > 7)
                {
                    nebulae[i].frame = 0;
                }
            }
         }

        finishLine = nebulae[sizeOfNebilae - 1].pos.x + 100;
        for (AnimData nebula : nebulae)
        {
            float pad{50};
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2 * pad,
                nebula.rec.height - 2 * pad};
            Rectangle scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height};
            if (CheckCollisionRecs(nebRec, scarfyRec))
            {
                lost = true;
            }
        }

        if (lost)
        {
            DrawText("You lost !", 200, 150, 30, RED);
        }

        else if (scarfyData.pos.x > finishLine)
        {
            DrawText("You Won !", 200, 150, 30, WHITE);
        }

        //Stop drawing
        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(backBuilding);
    UnloadTexture(farBuilding);
    UnloadTexture(foreGround);
    CloseWindow();

    return 0;
}