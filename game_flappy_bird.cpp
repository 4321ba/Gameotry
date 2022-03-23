#include "game_flappy_bird.h"

#include <iostream>
#include <cstdlib> // for random
#include <ctime>

#include "shapes.hpp"

GameFlappyBird::GameFlappyBird(): spike_x(-42), bird_pos(Screen::size.x*0.125, Screen::size.y*0.3), bird_velocity(0, 0) {
    randomize_spike_height();
}

void GameFlappyBird::randomize_spike_height() {
    spike_y_offset = Screen::size.y*0.5 * rand() / RAND_MAX /*0.0 .. 0.5*/;
}

void GameFlappyBird::input(int /*code*/) {
    bird_velocity = jump_speed;
}

bool GameFlappyBird::update(double delta, Screen& screen) {
    bird_velocity += gravity * delta;
    bird_pos += bird_velocity * delta;
    spike_x += spike_x_speed * delta;
    if (spike_x < -Screen::size.x * 0.4) {
        spike_x = Screen::size.x * 1.4;
        randomize_spike_height();
    }
    Circle bird(bird_pos, bird_pos + Vector(0, 2.25));
    Polygon spike_1(Vector(spike_x,              0), Vector(spike_x, Screen::size.y*0.1 + spike_y_offset /*0.1 .. 0.6*/), 3);
    Polygon spike_2(Vector(spike_x, Screen::size.y), Vector(spike_x, Screen::size.y*0.4 + spike_y_offset /*0.4 .. 0.9*/), 3);
    screen.draw_shape(bird);
    screen.draw_shape(spike_1);
    screen.draw_shape(spike_2);
    screen.draw_shape(upper_wall);
    screen.draw_shape(lower_wall);
    return spike_1.intersects_with(bird)
        or spike_2.intersects_with(bird)
        or upper_wall.intersects_with(bird)
        or lower_wall.intersects_with(bird);
}
