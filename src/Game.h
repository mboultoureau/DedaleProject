#pragma once

#include <memory>

#include "Scene.h"
#include "Screen.h"

class Game
{
public:
    Game();
    ~Game();

    void Run();
    void LoadScene();
private:
    Screen m_Screen;
};