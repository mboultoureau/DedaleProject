#include "GameMenu.h"

#include "SDL2/SDL_image.h"

GameMenu::GameMenu(SDL_Renderer* renderer)
{
    m_Renderer = renderer;
    m_TextureManager = new TextureManager(m_Renderer);
    m_BackgroundTexture = m_TextureManager->LoadImage("res/textures/game_menu.bmp");
}

GameMenu::~GameMenu()
{
    delete m_TextureManager;
}

void GameMenu::Update()
{

}

void GameMenu::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 242, 242, 242, 255);
    SDL_RenderClear(m_Renderer);

    SDL_Rect backgroundRect;
    backgroundRect.x = 0;
    backgroundRect.y = 0;
    backgroundRect.w = 640;
    backgroundRect.h = 480;

    SDL_RenderCopy(m_Renderer, m_BackgroundTexture, NULL, &backgroundRect);

    SDL_RenderPresent(m_Renderer);
}