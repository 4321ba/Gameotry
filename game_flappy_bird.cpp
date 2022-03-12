#include "game_flappy_bird.h"

#include <iostream>
#include <cstdlib> // for random

#include "shapes.hpp"
#include "screen.h"


GameFlappyBird::GameFlappyBird(): spike_x(-100), bird_pos(20, 0), bird_velocity(0, 0) {
    srand(time(NULL));
    randomize_spike_height();
}

void GameFlappyBird::randomize_spike_height() {
    spike_y_offset = rand() % 40;
}

void GameFlappyBird::input(int /*code*/) {
    bird_velocity = jump_speed;
}

bool GameFlappyBird::update(double delta) {
    bird_velocity = bird_velocity + gravity * delta;
    bird_pos = bird_pos + bird_velocity * delta;
    spike_x += spike_x_speed * delta;
    if (spike_x < -30) {
        spike_x = 150;
        randomize_spike_height();
    }
    Screen screen;
    Circle bird(bird_pos, bird_pos + Vector(3, 1));
    Polygon spike1(Vector(spike_x, 0), Vector(spike_x, 10 + spike_y_offset), 3);
    Polygon spike2(Vector(spike_x, 80), Vector(spike_x, 30 + spike_y_offset), 3);
    screen.draw_shape(bird);
    screen.draw_shape(spike1);
    screen.draw_shape(spike2);
    std::cout << spike_x << "\n";
    std::cout << screen;
    return (spike1.intersects_with(bird) or spike2.intersects_with(bird));
}
