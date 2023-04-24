#include "Player.h"

Player::Player(TextureManager* textureManager)
{
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
}