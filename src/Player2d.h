#pragma once

#include <array>

#include "TextureManager.h"
#include "Maze.h"

class Player2d
{
public:
    Player2d(SDL_Renderer* renderer, TextureManager* textureManager, Maze* maze);
    ~Player2d();

    void Update();
    void Render();
    void Move(int x, int y, int z);


    inline std::array<int, 3> GetPosition() const { return m_Position; }
private:
    std::array<int, 3> m_Position;
    
    Maze* m_Maze;
    SDL_Renderer* m_Renderer;
    SDL_Texture* m_Texture;
    TextureManager* m_TextureManager;
};