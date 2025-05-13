#ifndef BUTTON_H
#define BUTTON_H
#include "Rectangle.h"
#include <SDL2/SDL.h>
#include <print>

class UI;

class Button : public Rectangle
{
  public:
    Button(UI& uiManager, const SDL_Rect& rect) : _uiManager{uiManager}, Rectangle{rect}
    {
        setColour({255, 165, 0, 255});
    }

    void onMouseEnter() override
    {
        std::print("Hello mouse\n");
    }

    void onMouseExit() override
    {
        std::print("Bye bye mouse :(\n");
    }
    void onLeftClick() override;

  private:
    UI& _uiManager;
};

#endif