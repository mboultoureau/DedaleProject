#include "Player2d.h"

#include <iostream>
#include <cmath>

Player2d::Player2d(SDL_Renderer* renderer, TextureManager* textureManager, Maze* maze)
{
    m_Renderer = renderer;
    m_TextureManager = textureManager;
    m_Texture = m_TextureManager->LoadImage("res/textures/player.bmp");
    m_Maze = maze;

    m_Position = { 0, 0, 0 };
}

Player2d::~Player2d()
{
}

void Player2d::Update()
{
}

void Player2d::Render()
{
    int x = m_Position[0] * m_Maze->GetCellSize();
    int y = m_Position[1] * m_Maze->GetCellSize();

    SDL_Rect dstRect = { x + (int)(m_Maze->GetCellSize() * 0.25), y + (int)(m_Maze->GetCellSize() * 0.25), GetScreenWidth(), GetScreenHeight() };
    SDL_Rect srcRest = { 0, 0, 100, 100 };

    SDL_RenderCopy(m_Renderer, m_Texture, &srcRest, &dstRect);
    
    SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(m_Renderer, x, y, x + m_Maze->GetCellSize(), y);
    SDL_RenderDrawLine(m_Renderer, x + m_Maze->GetCellSize(), y, x + m_Maze->GetCellSize(), y + m_Maze->GetCellSize());
    SDL_RenderDrawLine(m_Renderer, x, y + m_Maze->GetCellSize(), x + m_Maze->GetCellSize(), y + m_Maze->GetCellSize());
    SDL_RenderDrawLine(m_Renderer, x, y, x, y + m_Maze->GetCellSize());
}

void Player2d::Move(int x, int y, int z)
{
    // Checking collisions on borders
    if (m_Position[0] + x < 0 || m_Position[0] + x >= (int)m_Maze->GetLength())
        x = 0;

    if (m_Position[1] + y < 0 || m_Position[1] + y >= (int)m_Maze->GetWidth())
        y = 0; 

    if (m_Position[2] + z < 0 || m_Position[2] + z >= (int)m_Maze->GetHeight())
        z = 0;

    // Checking collisions on walls
    if (x == 1 && (m_Maze->GetCell(m_Position[0], m_Position[1], m_Position[2]) & WALL_EAST))
        x = 0;

    if (x == -1 && (m_Maze->GetCell(m_Position[0], m_Position[1], m_Position[2]) & WALL_WEST))
        x = 0;

    if (y == 1 && (m_Maze->GetCell(m_Position[0], m_Position[1], m_Position[2]) & WALL_SOUTH))
        y = 0;

    if (y == -1 && (m_Maze->GetCell(m_Position[0], m_Position[1], m_Position[2]) & WALL_NORTH))
        y = 0;
    

    // Moving
    m_Position[0] += x;
    m_Position[1] += y;
    m_Position[2] += z;
}

void Player2d::Reset()
{
    m_Position = { 0, 0, 0 };
}