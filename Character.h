#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight);
    Vector2 getWorldPos() { return worldPos; }
    virtual Vector2 getScreenPos() override;
    virtual void tick(float deltaTime) override; 
    Rectangle getWeaponCollisionRec() { return weaponCollisionRec; };
    float getHealth() const { return health; }
    void takeDamage(float amount);
private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{   };
    float health{10.0f};
};
#endif