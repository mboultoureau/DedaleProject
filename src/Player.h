#pragma once

#include <array>
#include "TextureManager.h"

class Player
{
public:
    Player(SDL_Renderer* renderer, TextureManager* textureManager);
    ~Player();

    void Update();
    void Render();
private:
    std::array<int, 3> m_Position;
    SDL_Renderer* m_Renderer;
    SDL_Texture* m_Texture;
    TextureManager* m_TextureManager;
};