#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "raylib.h"
#include <vector>

class GameOver
{
public:
    GameOver();
    ~GameOver();

    void Show(float deltaTime, float windowWidth, float windowHeight);

private:
    Texture2D gameOverSprites[6];

    std::vector<std::pair<int, int>> letterIndices;

    int currentSprite;
    float timer;
    float spriteSwitchInterval;
    int letterIndex;
};

#endif
