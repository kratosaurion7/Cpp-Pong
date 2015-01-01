#pragma once

struct GameStructure;

#include "GameObject.h"

class Paddle : public GameObject
{
public:
    Paddle();
    ~Paddle();

    void Update(GameStructure*);
};

