#pragma once

#include "basetsd.h"

struct GameStructure;

class GameObject
{
public:
    GameObject();
    ~GameObject();

    float pos_x;
    float pos_y;

    int Height;
    int Width;

    UINT32 Color = 0x00FFFF;

    virtual void Update(GameStructure* context);
};

