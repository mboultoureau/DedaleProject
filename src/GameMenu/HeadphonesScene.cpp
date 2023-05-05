#include "HeadphonesScene.h"

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>

HeadphonesScene::HeadphonesScene(SDL_Renderer* renderer): m_SecondsElapsed(0.0f)
{
    m_Renderer = renderer;
    m_TextureManager = new TextureManager(m_Renderer);
    m_HeadphoneTexture = m_TextureManager->LoadImage("res/textures/headphones.bmp");
    m_Font = TTF_OpenFont("res/fonts/Roboto-Medium.ttf", 24);

    if (m_Font == NULL)
    {
        std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }
}

HeadphonesScene::~HeadphonesScene()
{
    delete m_TextureManager;
}

void HeadphonesScene::Update()
{
    m_SecondsElapsed += 1.0f / 60.0f;
}

void HeadphonesScene::Render()
{
    int alpha = 0;
    // Fade in the first 0.25s, then stay 3 seconds, then fade out the last 0.5s
    // If time > 3.75s, then the scene is over
    if (m_SecondsElapsed < 0.25f)
    {
        alpha = (int)(m_SecondsElapsed / 0.25f * 255);
    }
    else if (m_SecondsElapsed < 3.25f)
    {
        alpha = 255;
    }
    else if (m_SecondsElapsed < 3.75f)
    {
        alpha = (int)((3.75f - m_SecondsElapsed) / 0.5f * 255);
    }
    else
    {
        m_IsOver = true;
        return;
    }


    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_Renderer);

    int width, height;
    SDL_GetRendererOutputSize(m_Renderer, &width, &height);

    // Render text in the middle of the screen
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_Font, "This game requires the use of headphones.", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_Renderer, textSurface);

    SDL_Rect textRect;
    textRect.x = width / 2 - textSurface->w / 2;
    textRect.y = height / 2 - textSurface->h / 2 + 64;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;

    SDL_SetTextureAlphaMod(textTexture, alpha);
    SDL_RenderCopy(m_Renderer, textTexture, NULL, &textRect);

    // Render headphones image in the middle of the screen
    SDL_Rect headphonesRect;
    headphonesRect.x = width / 2 - 128 / 2;
    headphonesRect.y = height / 2 - 128 / 2 - 64;
    headphonesRect.w = 128;
    headphonesRect.h = 128;

    SDL_SetTextureAlphaMod(m_HeadphoneTexture, alpha);
    SDL_RenderCopy(m_Renderer, m_HeadphoneTexture, NULL, &headphonesRect);

    SDL_RenderPresent(m_Renderer);
}

void HeadphonesScene::HandleEvent(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN)
    {
        m_IsOver = true;
    }
}