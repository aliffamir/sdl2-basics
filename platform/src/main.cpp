#include "Window.h"
#include <SDL2/SDL.h>
#include <print>

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::print("Failed to initialise SDL! SDL Error: {}\n", SDL_GetError());
    }

    Window window{};

    bool running = true;
    SDL_Event e;

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
        }

        window.render();
        window.update();
    }

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}