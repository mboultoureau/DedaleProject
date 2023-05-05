#include "Level3d.h"

#include <iostream>
#include <GL/glew.h>

//class MazeGenerator
#include "../MazeGenerator.h"

Level3d::Level3d(SDL_Renderer* renderer)
{
    m_Renderer = renderer;
    m_TextureManager = new TextureManager(m_Renderer);
    m_Maze = new Maze("res/levels/level2.level", m_Renderer, m_TextureManager);
    m_Player = std::make_unique<Player2d>(m_Renderer, m_TextureManager, m_Maze);

    // génération du labyrinthe avec le constructeur de MazeGenerator
    MazeGenerator mazeGenerator(10, 10, 1); // Largeur, Longueur, Hauteur
}

Level3d::~Level3d()
{
    delete m_TextureManager;
}

void Level3d::Update()
{
    m_Player->Update();
}

void Level3d::Render()
{
    
}

void Level3d::HandleEvent(SDL_Event event)
{
    unsigned int x = 0, y = 0, z = 0;

    switch (event.type)
    {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_UP:
                    y = -1;
                    break;
                case SDLK_DOWN:
                    y = 1;
                    break;
                case SDLK_LEFT:
                    x = -1;
                    break;
                case SDLK_RIGHT:
                    x = 1;
                    break;
                case SDLK_r:
                    m_Player->Reset();
                    break;
                default:
                    break;
            }
            break;
    }

    m_Player->Move(x, y, z);
}

void Level3d::InitOpenGL()
{
    GLuint programId = glCreateProgram();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);


}