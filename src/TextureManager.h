#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class TextureManager
{
public:
    TextureManager(SDL_Renderer* renderer);
    ~TextureManager();

    SDL_Texture* LoadImage(const std::string& imagePath);
private:
    SDL_Renderer* m_Renderer;
    std::vector<SDL_Texture*> m_Textures;
};