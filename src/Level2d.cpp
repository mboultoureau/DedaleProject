#include "Level2d.h"

#include <iostream>

//class MazeGenerator
#include "MazeGenerator.h"

Level2d::Level2d(SDL_Renderer* renderer)
{
    m_Renderer = renderer;
    m_TextureManager = new TextureManager(m_Renderer);
    m_Maze = std::make_unique<Maze>("res/levels/level2.level", m_Renderer, m_TextureManager);
    m_Player = std::make_unique<Player2d>(m_Renderer, m_TextureManager);

    // génération du labyrinthe avec le constructeur de MazeGenerator
    MazeGenerator mazeGenerator(10, 10, 1); // Largeur, Longueur, Hauteur
}

Level2d::~Level2d()
{
    delete m_TextureManager;
}

void Level2d::Update()
{
    m_Player->Update();
}

void Level2d::Render()
{
    // Clear screen
    SDL_SetRenderDrawColor(m_Renderer, 242, 242, 242, 255);
    SDL_RenderClear(m_Renderer);

    // Render scene
    m_Maze->Render();
    m_Player->Render();

    // Render scene
    SDL_RenderPresent(m_Renderer);
}

void Level2d::HandleEvent(SDL_Event event)
{
    int x = 0, y = 0, z = 0;
    const int speed = 5;

    switch (event.type)
    {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_UP:
                    y = -speed;
                    break;
                case SDLK_DOWN:
                    y = speed;
                    break;
                case SDLK_LEFT:
                    x = -speed;
                    break;
                case SDLK_RIGHT:
                    x = speed;
                    break;
                default:
                    break;
            }
            break;
    }

    m_Player->Move(x, y, z);
}