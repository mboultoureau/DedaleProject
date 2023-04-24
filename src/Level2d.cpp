#include "Level2d.h"

#include <iostream>

//class MazeGenerator
#include "MazeGenerator.h"

Level2d::Level2d(SDL_Renderer* renderer)
{
    m_Renderer = renderer;
    m_TextureManager = new TextureManager(m_Renderer);
    m_Maze = std::make_unique<Maze>("res/levels/level2.level", m_Renderer, m_TextureManager);
    m_Player = std::make_unique<Player>(m_Renderer, m_TextureManager);

    //génération du labyrinthe avec le constructeur de MazeGenerator
    MazeGenerator mazeGenerator(10, 10, 1); //Largeur, Longueur, Hauteur
    //MazeGenerator m_MazeGenerator = new MazeGenerator(10, 10, 1);
}

Level2d::~Level2d()
{
    delete m_TextureManager;
}

void Level2d::Update()
{

}

void Level2d::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 242, 242, 242, 255);
    SDL_RenderClear(m_Renderer);

    m_Maze->Render();
    m_Player->Render();

    // Render scene
    SDL_RenderPresent(m_Renderer);
}