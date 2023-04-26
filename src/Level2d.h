#pragma once

#include "Maze.h"
#include "Scene.h"
#include "TextureManager.h"
#include "Player2d.h"

#include <memory>

class Level2d : public Scene
{
public:
    Level2d(SDL_Renderer* renderer);
    ~Level2d();

    void Update();
    void Render();
    void HandleEvent(SDL_Event event);
private:
    std::unique_ptr<Player2d> m_Player;

    Maze* m_Maze;
    SDL_Renderer* m_Renderer;
    TextureManager* m_TextureManager;
};