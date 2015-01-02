#pragma once

struct GameStructure;

#include "GameObject.h"


class Ball : public GameObject
{
public:
    Ball();
    ~Ball();

    void Update(GameStructure* context);
};

