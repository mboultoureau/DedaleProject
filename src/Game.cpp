#include <SDL2/SDL.h>

#include "Game.h"
#include "GameMenu/GameMenu.h"
#include "GameMenu/HeadphonesScene.h"
#include "Level2d/Level2d.h"

Game::Game() : m_Screen()
{
}

Game::~Game()
{
}

void Game::Run()
{
    Scene* currentScene = nullptr;
    GameMenu* gameMenu = new GameMenu(m_Screen.GetRenderer());
    HeadphonesScene* headphonesScene = new HeadphonesScene(m_Screen.GetRenderer());
    Level2d* level2d = new Level2d(m_Screen.GetRenderer());
    currentScene = headphonesScene;

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

            // Event is handled by the current scene
            currentScene->HandleEvent(event);
        }

        if (currentScene)
        {
            currentScene->Update();
            currentScene->Render();
        }

        // Switch to the next scene if the current scene is over
        if (currentScene == headphonesScene && headphonesScene->IsOver())
        {
            currentScene = gameMenu;
        }
        // else if (currentScene == gameMenu && gameMenu->IsOver())
        // {
        //     currentScene = level2d;
        // }
        // else if (currentScene == level2d && level2d->IsOver())
        // {
        //     currentScene = nullptr;
        // }
    
        SDL_Delay(16);
    }
}