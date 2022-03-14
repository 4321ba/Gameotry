#ifndef GAME_FLAPPY_BIRD_H
#define GAME_FLAPPY_BIRD_H

#include "vectormath.hpp"
#include "game.h"

class GameFlappyBird: public Game {
    const Vector gravity = Vector(0, 40); // block per sec^2
    const Vector jump_speed = Vector(0, -32); // block per sec
    const double spike_x_speed = -45; // block per sec
    
    double spike_x;
    double spike_y_offset;
    Vector bird_pos;
    Vector bird_velocity;
    
    void randomize_spike_height();
public:
    GameFlappyBird();
    void input(int code);
    bool update(double delta, Screen& screen);
};

#endif // GAME_FLAPPY_BIRD_H
