#ifndef HEALTH_H
#define HEALTH_H

#include "raylib.h"

void InitHealthSystem(const char *texturePath, const char *hpIconPath);

void UnloadHealthSystem();

void DrawHealth(float health, Vector2 position, float spacing, float scale);

#endif
