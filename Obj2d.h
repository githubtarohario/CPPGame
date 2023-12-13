#pragma once

#include "./GameLib/game_lib.h"
#include "./GameLib/obj2d_data.h"

class OBJ2D
{
public:
    GameLib::SpriteData* sprData;
    VECTOR2 position;
    VECTOR2 scale;
    float rotation;
    VECTOR4 color;
    GameLib::Blender::BLEND_STATE blendState;

    int state;
    VECTOR2 velocity;

    OBJ2D() { init(); }

    void init()
    {
        sprData = nullptr;
        position = {};
        scale = { 1,1 };
        rotation = 0.0f;
        color = { 1,1,1,1 };
        blendState = GameLib::Blender::BLEND_STATE::BS_ALPHA;

        state = 0;
        velocity = {};
    }

    void clear() { init(); }

    void draw();
};
