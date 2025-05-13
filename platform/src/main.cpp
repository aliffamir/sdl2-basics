#include "Rectangle.h"
#include "Window.h"
#include <SDL2/SDL.h>
#include <print>

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::print("Failed to initialise SDL! SDL Error: {}\n", SDL_GetError());
    }

    Window window;
    // SDL_Rect is a simple struct of 4 members
    // x and y members represent the position of the top left corner of the rectangle
    // w and h members represent the width and height of the rectange respectively
    Rectangle rectangle{SDL_Rect{100, 100, 50, 50}};

    bool running = true;
    SDL_Event e;

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            rectangle.handleEvent(e);
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
        }

        window.render();
        rectangle.Render(window.getSurface());
        window.update();
    }

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}