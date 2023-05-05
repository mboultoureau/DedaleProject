#pragma once

#include "../Maze.h"
#include "../Scene.h"
#include "../TextureManager.h"
#include "../Level2d/Player2d.h"

#include <memory>

class Level3d : public Scene
{
public:
    Level3d(SDL_Renderer* renderer);
    ~Level3d();

    void Update();
    void Render();
    void HandleEvent(SDL_Event event);

    void InitOpenGL();
private:
    std::unique_ptr<Player2d> m_Player;

    Maze* m_Maze;
    SDL_Renderer* m_Renderer;
    TextureManager* m_TextureManager;
};