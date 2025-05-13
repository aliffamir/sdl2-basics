#ifndef REDRECTANGLE_H
#define REDRECTANGLE_H
#include "Rectangle.h"

class RedRectangle : public Rectangle
{
  public:
    RedRectangle(const SDL_Rect& rect) : Rectangle{rect}
    {
        setColour({255, 0, 0, 255});
    }
};

#endif