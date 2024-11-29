#include "raylib.h"
#include "C:/raylib/raylib/src/raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "prop.h"
#include "health.h"
#include "gameover.h"
#include <string>

int main()
{
    const int windowWidth{720};
    const int windowHeight{720};
    InitWindow(windowWidth, windowHeight, "Stabby Stabs!");

    Texture2D map = LoadTexture("nature_tileset/worldMap.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{6.0f};

    Character knight{windowWidth, windowHeight};

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};

    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy slime =
        {Vector2{800.f, 600.f},
         LoadTexture("characters/slime_idle_spritesheet.png"),
         LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy *enemies[]{
        &goblin,
        &slime};

    GameOver gameOver;

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    InitHealthSystem("health/heart.png", "health/life.png");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        if (!knight.getAlive())
        {
            gameOver.Show(GetFrameTime(), windowWidth, windowHeight);
            EndDrawing();
            continue;
        }

        DrawHealth(knight.getHealth(), Vector2{55.f, 45.f}, 15.f, 3.0f);

        knight.tick(GetFrameTime());

        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_SPACE))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }
    UnloadTexture(map);
    UnloadHealthSystem();
    CloseWindow();
}