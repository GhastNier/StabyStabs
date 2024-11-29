#include "GameOver.h"

float spriteScale;

GameOver::GameOver()
    : currentSprite(0), timer(0.0f), spriteSwitchInterval(0.2f), letterIndex(0)
{
    
    for (int i = 0; i < 4; i++)
    {
        gameOverSprites[i] = LoadTexture(TextFormat("gameover/Game_Over_Glitch_%d.png", i));
    }

    
    letterIndices = {
        {1, 7}, {1, 1}, {2, 5}, {1, 5}, {9, 8}, {2, 7}, {3, 6}, {1, 5}, {3, 2}, {8, 7}
    };

    
    spriteScale = 5.5f;  
}

GameOver::~GameOver()
{
    
    for (int i = 0; i < 4; i++)
    {
        UnloadTexture(gameOverSprites[i]);
    }
}

void GameOver::Show(float deltaTime, float windowWidth, float windowHeight)
{
    
    timer += deltaTime;
    
    
    if (timer >= spriteSwitchInterval)
    {
        timer = 0.0f;  
        currentSprite = (currentSprite + 1) % 4;  
    }

    
    float letterWidth = gameOverSprites[0].width / 8.0f;  
    float letterHeight = gameOverSprites[0].height / 12.0f;  

    
    float totalWidth = letterWidth * letterIndices.size() * spriteScale;  

    
    float offsetX = (windowWidth - totalWidth) / 2.0f;  

    
    float startY = windowHeight / 2.0f - letterHeight * spriteScale / 2.0f;  

    
    for (int i = 0; i < letterIndices.size(); i++)
    {
        
        int row = letterIndices[i].first - 1;  
        int col = letterIndices[i].second - 1;  

        
        Rectangle sourceRect = {
            col * letterWidth,    
            row * letterHeight,   
            letterWidth,          
            letterHeight          
        };

        
        float posX = offsetX + i * letterWidth * spriteScale;  

        
        DrawTexturePro(gameOverSprites[currentSprite], sourceRect, 
            Rectangle{
                posX,                          
                startY,                         
                letterWidth * spriteScale,     
                letterHeight * spriteScale     
            }, 
            Vector2{0, 0}, 0.0f, WHITE);
    }
}
