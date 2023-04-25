#pragma once

#include <SDL2/SDL.h>

class Scene
{
public:
    virtual ~Scene() {};

    virtual void Update() {};
    virtual void Render() {};
    virtual void HandleEvent(SDL_Event) {};
};