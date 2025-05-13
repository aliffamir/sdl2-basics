#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL.h>

class Window
{
  public:
    Window()
    {
        _sdlWindow = SDL_CreateWindow("Hello Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 400, 0);
    }

    void render()
    {
        SDL_FillRect(getSurface(), nullptr, SDL_MapRGB(getSurface()->format, 255, 255, 255));
    }

    void update()
    {
        SDL_UpdateWindowSurface(_sdlWindow);
    }

    // Returns a pointer to the Window's surface object
    // Each window will have a surface that we can render other objects on (textures etc.)
    SDL_Surface* getSurface() const
    {
        return SDL_GetWindowSurface(_sdlWindow);
    }

    // delete copy constructor and copy assignment
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // destructor
    ~Window()
    {
        if (_sdlWindow && SDL_WasInit(SDL_INIT_VIDEO))
        {
            SDL_DestroyWindow(_sdlWindow);
        }
    }

  private:
    SDL_Window* _sdlWindow{nullptr};
};

#endif