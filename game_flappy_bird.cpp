#include "game_flappy_bird.h"

#include <iostream>
#include <cstdlib> // for random
#include <ctime>

#include "shapes.hpp"
//TODO mágikus számok helyett screen.size?

GameFlappyBird::GameFlappyBird(): spike_x(-42), bird_pos(12, 6), bird_velocity(0, 0) {
    srand(time(NULL));
    randomize_spike_height();
}

void GameFlappyBird::randomize_spike_height() {
    spike_y_offset = rand() * 25.0 / RAND_MAX;
}

void GameFlappyBird::input(int /*code*/) {
    bird_velocity = jump_speed;
}

bool GameFlappyBird::update(double delta, Screen& screen) {
    bird_velocity = bird_velocity + gravity * delta;
    bird_pos = bird_pos + bird_velocity * delta;
    spike_x += spike_x_speed * delta;
    if (spike_x < -20) {
        spike_x = screen.size.x + 20;
        randomize_spike_height();
    }
    Circle bird(bird_pos, bird_pos + Vector(2, 1));
    Polygon spike1(Vector(spike_x, 0), Vector(spike_x, 5 + spike_y_offset), 3);
    Polygon spike2(Vector(spike_x, 50), Vector(spike_x, 20 + spike_y_offset), 3);
    screen.draw_shape(bird);
    screen.draw_shape(spike1);
    screen.draw_shape(spike2);
    return (spike1.intersects_with(bird) or spike2.intersects_with(bird));
}
