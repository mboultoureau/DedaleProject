#pragma once

#include <array>
#include "TextureManager.h"

class Player
{
public:
    Player(TextureManager* textureManager);
    ~Player();

    void Update();
    void Render();
private:
    std::array<int, 3> m_Position;
    SDL_Texture* m_Texture;
    TextureManager* m_TextureManager;
};