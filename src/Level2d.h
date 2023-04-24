#pragma once

#include "Maze.h"
#include "Scene.h"
#include "TextureManager.h"
#include "Player.h"

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
    std::unique_ptr<Player> m_Player;

    SDL_Renderer* m_Renderer;
    TextureManager* m_TextureManager;
};