#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <SDL2/SDL.h>

class Rectangle
{
  public:
    Rectangle(const SDL_Rect& rect) : _rect{rect}
    {
    }

    void Render(SDL_Surface* windowSurface) const
    {
        SDL_FillRect(windowSurface, &_rect, SDL_MapRGB(windowSurface->format, 0, 255, 0));
    }

  private:
    SDL_Rect _rect{};
};

#endif