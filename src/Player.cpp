#include "Player.h"

Player::Player(SDL_Renderer* renderer, TextureManager* textureManager)
{
    m_Renderer = renderer;
    m_TextureManager = textureManager;
    m_Texture = m_TextureManager->LoadImage("res/textures/player.bmp");

    m_Position = { 0, 0, 0 };
}

Player::~Player()
{
}

void Player::Update()
{

}

void Player::Render()
{
    SDL_Rect dstRect = { m_Position[0], m_Position[1], 32, 32 };
    SDL_Rect srcRest = { 0, 0, 100, 100 };

    SDL_RenderCopy(m_Renderer, m_Texture, &srcRest, &dstRect);
}