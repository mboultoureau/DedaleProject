#pragma once

#include "../Scene.h"
#include "../TextureManager.h"

#include "SDL2/SDL_ttf.h"

class HeadphonesScene : public Scene
{
public:
    HeadphonesScene(SDL_Renderer* renderer);
    ~HeadphonesScene();

    void Update();
    void Render();
    void HandleEvent(SDL_Event event);
    bool IsOver() { return m_IsOver; }
private:
    SDL_Renderer* m_Renderer;
    SDL_Texture* m_HeadphoneTexture;
    TextureManager* m_TextureManager;
    TTF_Font* m_Font;
    bool m_IsOver;

    float m_SecondsElapsed;
};