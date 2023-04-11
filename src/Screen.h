#pragma once

#include <SDL2/SDL.h>

class Screen
{
public:
    Screen();
    ~Screen();

    SDL_Renderer* GetRenderer();
private:
    SDL_Window *m_Window;
    SDL_Renderer *m_Renderer;
};