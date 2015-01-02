#pragma once

#include "Ball.h"

#include "Paddle.h"

#include "BaseList.h"

enum Players{
    PLAYER_1,
    PLAYER_2,
    
    TOTAL_PLAYERS
};

#define BALL_NUMBER 1

struct GameStructure{
    int area_width;
    int area_height;

    BaseList<Ball*>* Balls;

    BaseList<Paddle*>* Paddles;

    ~GameStructure()
    {
        delete(Balls);
        delete(Paddles);
    }
};