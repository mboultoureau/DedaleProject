#include "Screen.h"

#include <iostream>
#include <SDL2/SDL.h>

Screen::Screen()
{
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "SDL initialization error: " << SDL_GetError() << std::endl;
        return;
    }

    m_Window = SDL_CreateWindow("BlindMaze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (NULL == m_Window)
    {
        std::cout << "SDL window creation error: " << SDL_GetError() << std::endl;
        return;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == m_Renderer)
    {
        std::cout << "SDL renderer creation error: " << SDL_GetError() << std::endl;
        return;
    }
}

Screen::~Screen()
{
    if (NULL != m_Renderer)
        SDL_DestroyRenderer(m_Renderer);

    if (NULL != m_Window)
        SDL_DestroyWindow(m_Window);

    SDL_Quit();
}

SDL_Renderer* Screen::GetRenderer()
{
    return m_Renderer;
}