#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <SDL2/SDL.h>
#include <iostream>

class Rectangle
{
  public:
    Rectangle(const SDL_Rect& rect) : _rect{rect}
    {
    }

    virtual void onMouseEnter() {};
    virtual void onMouseExit() {};
    virtual void onLeftClick() {};

    void render(SDL_Surface* windowSurface) const
    {
        auto [r, g, b, a]{isPointerHovering ? _hoverColour : _colour};
        SDL_FillRect(windowSurface, &_rect, SDL_MapRGB(windowSurface->format, r, g, b));
    }

    void handleEvent(SDL_Event& e)
    {
        if (e.type == SDL_MOUSEMOTION)
        {
            bool wasPointerHovering{isPointerHovering};
            isPointerHovering = isWithinRect(e.motion.x, e.motion.y);
            if (!wasPointerHovering && isPointerHovering)
            {
                onMouseEnter();
            }
            else if (wasPointerHovering && !isPointerHovering)
            {
                onMouseExit();
            }
        }
        else if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_LEAVE)
        {
            if (isPointerHovering)
                onMouseExit();
            isPointerHovering = false;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (isPointerHovering && e.button.button == SDL_BUTTON_LEFT)
            {
                onLeftClick();
            }
        }
    }

    void setColour(const SDL_Color& colour)
    {
        _colour = colour;
    }

    void setHoverColour(const SDL_Color& colour)
    {
        _hoverColour = colour;
    }

    SDL_Color getColour() const
    {
        return _colour;
    }

    SDL_Color getHoverColour() const
    {
        return _hoverColour;
    }

    virtual ~Rectangle() {};

  private:
    SDL_Rect _rect{};
    // Default to green in RGBA format
    SDL_Color _colour{0, 255, 0, 255};
    SDL_Color _hoverColour{0, 0, 255, 255};

    bool isPointerHovering{false};
    bool isWithinRect(int x, int y)
    {
        // Too far left
        if (x < _rect.x)
            return false;
        // Too far right
        if (x > _rect.x + _rect.w)
            return false;
        // Too far up
        if (y < _rect.y)
            return false;
        // Too far down
        if (y > _rect.y + _rect.h)
            return false;

        // If we got this far, that means the
        // point is within the rectangle
        return true;
    }
};

#endif