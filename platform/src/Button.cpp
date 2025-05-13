#include "Button.h"
#include "UI.h"
#include <SDL2/SDL.h>
void Button::onLeftClick()
{
    // _uiManager.setRectangleColours({159, 90, 253, 255});
    SDL_Event e{SDL_QUIT};
    SDL_PushEvent(&e);
}