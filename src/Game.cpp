#include <SDL2/SDL.h>

#include "Game.h"
#include "GameMenu.h"
#include "Level2d.h"

Game::Game() : m_Screen()
{
}

Game::~Game()
{

}

void Game::Run()
{
    Scene* currentScene = nullptr;
    // GameMenu* gameMenu = new GameMenu(m_Screen.GetRenderer());
    Level2d* level2d = new Level2d(m_Screen.GetRenderer());
    currentScene = level2d;

    SDL_Event event;
    SDL_bool quit = SDL_FALSE;

    // Game loop
    while (!quit)
    {
        // Event loop
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                quit = SDL_TRUE;
        }

        if (currentScene)
        {
            currentScene->Update();
            currentScene->Render();
        }
    
        SDL_Delay(16);
    }
}