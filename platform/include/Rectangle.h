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
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_RIGHT:
                _xVel = 1;
                break;
            case SDLK_LEFT:
                std::cout << "moving left\n";
                _xVel = -1;
                break;
            case SDLK_UP:
                std::cout << "moving up\n";
                _yVel = -1;
                break;
            case SDLK_DOWN:
                std::cout << "moving down\n";
                _yVel = 1;
                break;
            }
        }
        else if (e.type == SDL_KEYUP)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_RIGHT:
                if (_xVel > 0)
                {
                    _xVel = 0;
                }
                break;
            case SDLK_LEFT:
                if (_xVel < 0)
                {
                    _xVel = 0;
                }
                break;
            case SDLK_UP:
                if (_yVel < 0)
                {
                    _yVel = 0;
                }
                break;
            case SDLK_DOWN:
                if (_yVel > 0)
                {

                    _yVel = 0;
                }
                break;
            }
        }

        _rect.x += _xVel;
        _rect.y += _yVel;
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
    int _xVel{0};
    int _yVel{0};
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