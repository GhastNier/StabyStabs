#include "health.h"

static Texture2D hearts;

static int heartWidth;
static int heartHeight;
static Texture2D hpIcon;
static int hpIconWidth;
static int hpIconHeight;

void InitHealthSystem(const char *texturePath, const char *hpIconPath)
{
    hearts = LoadTexture(texturePath);
    hpIcon = LoadTexture(hpIconPath);
    heartWidth = hearts.width / 5;
    heartHeight = hearts.height;
    hpIconWidth = hpIcon.width / 3;
    hpIconHeight = hpIcon.height;
}

void UnloadHealthSystem()
{
    UnloadTexture(hearts);
    UnloadTexture(hpIcon);
}

void DrawHealth(float health, Vector2 position, float spacing, float scale)
{

    float scaledHpWidth = hpIconWidth * scale + 2.f;
    float scaledHpHeight = hpIconHeight * scale + 2.f;
    Rectangle hpSource{0.f, 0.f, static_cast<float>(hpIconWidth), static_cast<float>(hpIconHeight)};
    Rectangle hpDest{position.x, position.y, scaledHpWidth, scaledHpHeight};
    DrawTexturePro(hpIcon, hpSource, hpDest, Vector2{0.f, 0.f}, 0.f, WHITE);

    int fullHearts = static_cast<int>(health) / 2;
    int halfHeart = static_cast<int>(health) % 2;
    int emptyHearts = 5 - fullHearts - halfHeart;

    float scaledWidth = heartWidth * scale;
    float scaledHeight = heartHeight * scale;

    for (int i = 0; i < fullHearts; i++)
    {
        Rectangle source{0.f, 0.f, static_cast<float>(heartWidth), static_cast<float>(heartHeight)};
        Rectangle dest{position.x + scaledHpWidth + i * (scaledWidth + spacing), position.y, scaledWidth, scaledHeight};
        DrawTexturePro(hearts, source, dest, Vector2{0.f, 0.f}, 0.f, WHITE);
    }

    if (halfHeart == 1)
    {
        Rectangle source{heartWidth * 2, 0.f, static_cast<float>(heartWidth), static_cast<float>(heartHeight)};
        Rectangle dest{position.x + scaledHpWidth + fullHearts * (scaledWidth + spacing), position.y, scaledWidth, scaledHeight};
        DrawTexturePro(hearts, source, dest, Vector2{0.f, 0.f}, 0.f, WHITE);
    }

    for (int i = 0; i < emptyHearts; i++)
    {
        Rectangle source{heartWidth * 4, 0.f, static_cast<float>(heartWidth), static_cast<float>(heartHeight)};
        Rectangle dest{position.x + scaledHpWidth + (fullHearts + halfHeart + i) * (scaledWidth + spacing), position.y, scaledWidth, scaledHeight};
        DrawTexturePro(hearts, source, dest, Vector2{0.f, 0.f}, 0.f, WHITE);
    }
}
