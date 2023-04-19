#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager(SDL_Renderer* renderer)
{
    m_Renderer = renderer;
}

TextureManager::~TextureManager()
{
    // Destroy all textures
    for (auto texture : m_Textures)
        SDL_DestroyTexture(texture);
}

SDL_Texture* TextureManager::LoadImage(const std::string& imagePath)
{
    // Load image
    SDL_Surface *image = SDL_LoadBMP(imagePath.c_str());
    if (NULL == image)
    {
        std::cout << "Image loading error \"" << imagePath << "\": " << SDL_GetError() << std::endl;
        return NULL;
    }

    // Create texture from image
    SDL_Texture *texture = SDL_CreateTextureFromSurface(m_Renderer, image);
    SDL_FreeSurface(image);

    if (NULL == texture)
    {
        std::cout << "Texture creation error \"" << imagePath << "\": " << SDL_GetError() << std::endl;
        return NULL;
    }

    m_Textures.push_back(texture);

    return texture;
}