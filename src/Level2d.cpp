#include "Level2d.h"

#include "SDL2/SDL_image.h"

#include <iostream>

//class MazeGenerator
#include "MazeGenerator.h"

Level2d::Level2d(SDL_Renderer* renderer)
{
    m_Renderer = renderer;
    m_TextureManager = new TextureManager(m_Renderer);
    m_WallsTexture = m_TextureManager->LoadImage("res/textures/walls.bmp");
    m_Maze = std::make_unique<Maze>("");

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

    SDL_Rect wallDestRect;
    SDL_Rect wallSrcRect;

    wallDestRect.w = 40;
    wallDestRect.h = 40;

    wallSrcRect.w = 40;
    wallSrcRect.h = 40;
    wallSrcRect.y = 0;

    for (unsigned int z = 0; z < m_Maze->GetHeight(); z++)
    {
        for (unsigned int y = 0; y < m_Maze->GetWidth(); y++)
        {
            for (unsigned int x = 0; x < m_Maze->GetLength(); x++)
            {
                wallDestRect.x = x * 40 + 5;
                wallDestRect.y = y * 40 + 5;

                wallSrcRect.x = m_Maze->GetCell(x, y, z) * 40;

                SDL_RenderCopy(m_Renderer, m_WallsTexture, &wallSrcRect, &wallDestRect);
            }
        }
    }

    // Draw north border
    SDL_Rect border;
    border.w = 40 * m_Maze->GetWidth();
    border.h = 5;
    border.x = 0;
    border.y = 0;
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(m_Renderer, &border);

    border.y = m_Maze->GetLength() * 40 + 5;
    SDL_RenderFillRect(m_Renderer, &border);

    border.w = 5;
    border.h = m_Maze->GetLength() * 40 + 5;
    border.x = 0;
    border.y = 0;
    SDL_RenderFillRect(m_Renderer, &border);

    border.x = m_Maze->GetWidth() * 40 - 5;
    SDL_RenderFillRect(m_Renderer, &border);

    SDL_RenderPresent(m_Renderer);
}