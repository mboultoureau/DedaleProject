#include "Player2d.h"

Player2d::Player2d(SDL_Renderer* renderer, TextureManager* textureManager, Maze* maze)
{
    m_Renderer = renderer;
    m_TextureManager = textureManager;
    m_Texture = m_TextureManager->LoadImage("res/textures/player.bmp");
    m_Maze = maze;

    m_Position = { 5, 5, 0 };
}

Player2d::~Player2d()
{
}

void Player2d::Update()
{
    // int x = 0, y = 0;
    // // Get mouse position
    // SDL_GetMouseState(&x, &y);

    // // Set player position
    // m_Position[0] = x - 16;
    // m_Position[1] = y - 16;
}

void Player2d::Render()
{
    SDL_Rect dstRect = { m_Position[0], m_Position[1], 32, 32 };
    SDL_Rect srcRest = { 0, 0, 100, 100 };

    SDL_RenderCopy(m_Renderer, m_Texture, &srcRest, &dstRect);
}

void Player2d::Move(int x, int y, int z)
{
    // Checking collision




    m_Position[0] += x;
    m_Position[1] += y;
    m_Position[2] += z;
}