#pragma once

struct GameStructure;

class GameObject
{
public:
    GameObject();
    ~GameObject();

    int pos_x;
    int pos_y;

    int Height;
    int Width;;

    virtual void Update(GameStructure* context);
};

