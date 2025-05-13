#ifndef UI_H
#define UI_H
// #include "Rectangle.h"
#include "RedRectangle.h"
#include <SDL2/SDL.h>
#include <memory>

class UI
{
  public:
    UI()
    {
        int rowCount{5};
        int colCount{12};

        _rectangles.reserve(rowCount * colCount);
        for (int row{0}; row < rowCount; ++row)
        {
            for (int col{0}; col < colCount; ++col)
            {
                bool useGreen{(row + col) % 2 == 0};
                _rectangles.emplace_back(useGreen
                                             ? std::make_unique<Rectangle>(SDL_Rect{60 * col, 60 * row, 50, 50})
                                             : std::make_unique<RedRectangle>(SDL_Rect{60 * col, 60 * row, 50, 50}));
            }
        }
    }
    void render(SDL_Surface* windowSurface) const
    {
        for (const auto& rectangle : _rectangles)
        {
            rectangle->render(windowSurface);
        }
    }

    void handleEvent(SDL_Event& e)
    {
        for (auto& rectangle : _rectangles)
        {
            rectangle->handleEvent(e);
        }
    }

  private:
    std::vector<std::unique_ptr<Rectangle>> _rectangles{};
};

#endif