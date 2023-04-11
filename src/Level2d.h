#pragma once

#include "Maze.h"
#include "Scene.h"
#include "TextureManager.h"

#include <memory>

class Level2d : public Scene
{
public:
    Level2d(SDL_Renderer* renderer);
    ~Level2d();

    void Update();
    void Render();
private:
    std::unique_ptr<Maze> m_Maze;
    SDL_Renderer* m_Renderer;
    SDL_Texture* m_WallsTexture;
    TextureManager* m_TextureManager;
};