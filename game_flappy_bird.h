#ifndef GAME_FLAPPY_BIRD_H
#define GAME_FLAPPY_BIRD_H

#include <cstdlib> // rand

#include "vectormath.hpp"
#include "game.h"

class GameFlappyBird: public Game {
    double spike_x;
    int spike_y_offset;
    Vector bird_pos;
    Vector bird_velocity;
    const Vector gravity = Vector(0, 0.01);
    void randomize_spike_height() { spike_y_offset = rand() % 40; }
public:
    GameFlappyBird(): spike_x(-100), bird_pos(20, 0), bird_velocity(0, 0) {
        randomize_spike_height();
    }
    void input(int code);
    void draw_frame();
    bool tick_physics(double delta);
};

#endif // GAME_FLAPPY_BIRD_H
