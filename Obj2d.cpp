#include "Obj2d.h"

void OBJ2D::draw()
{
    if (sprData)
    {
        auto oldState = GameLib::getBlendMode();
        GameLib::setBlendMode(blendState);
        sprData->draw(position, scale, rotation, color);
        GameLib::setBlendMode(oldState);
    }
}
