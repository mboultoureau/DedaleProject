#pragma once

#include "Scene.h"
#include "TextureManager.h"

class GameMenu : public Scene
{
public:
    GameMenu(SDL_Renderer* renderer);
    ~GameMenu();

    void Update();
    void Render();
private:
    SDL_Renderer* m_Renderer;
    SDL_Texture* m_BackgroundTexture;
    TextureManager* m_TextureManager;
};