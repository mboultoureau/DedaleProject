#include "Screen.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>
#include <GL/glut.h>

Screen::Screen()
{
    // SDL initialization
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "SDL initialization error: " << SDL_GetError() << std::endl;
        return;
    }

    // Set OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create window
    m_Window = SDL_CreateWindow("BlindMaze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (NULL == m_Window)
    {
        std::cout << "SDL window creation error: " << SDL_GetError() << std::endl;
        return;
    }

    // Create OpenGL context
    m_Context = SDL_GL_CreateContext(m_Window);
    if (NULL == m_Context)
    {
        std::cout << "SDL OpenGL context creation error: " << SDL_GetError() << std::endl;
        return;
    }

    // Create renderer
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == m_Renderer)
    {
        std::cout << "SDL renderer creation error: " << SDL_GetError() << std::endl;
        return;
    }

    // Set minimum window size
    // SDL BUG: Minimum window size MUST be set after creating the renderer (https://github.com/libsdl-org/SDL/issues/1408)
    SDL_SetWindowMinimumSize(m_Window, 640, 480);

    // Initialize SDL_ttf
    if (0 != TTF_Init())
    {
        std::cout << "SDL_ttf initialization error: " << TTF_GetError() << std::endl;
        return;
    }

    // Initialize GLEW
    GLenum glewError = glewInit();
    if (GLEW_OK != glewError)
    {
        std::cout << "GLEW initialization error: " << glewGetErrorString(glewError) << std::endl;
        return;
    }

    // Use VSync: 0 on success, -1 if not supported
    if (0 > SDL_GL_SetSwapInterval(1))
    {
        std::cout << "SDL VSync error: " << SDL_GetError() << std::endl;
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