#include "game_flappy_bird.h"

#include <iostream>

#include "shapes.hpp"
#include "screen.h"

void GameFlappyBird::input(int /*code*/) {
    bird_velocity = Vector(0, -0.6);
}

void GameFlappyBird::draw_frame() {
    Screen screen;
    
    Circle bird(bird_pos, bird_pos + Vector(3, 1));
    screen.draw_shape(bird);
    
    Polygon spike1(Vector(spike_x, 0), Vector(spike_x, 10 + spike_y_offset), 3);
    screen.draw_shape(spike1);
    Polygon spike2(Vector(spike_x, 80), Vector(spike_x, 30 + spike_y_offset), 3);
    screen.draw_shape(spike2);
    
    std::cout << screen;
}

bool GameFlappyBird::tick_physics(double /*delta*/) {//TODO ofc használni deltát
    bird_velocity = bird_velocity + gravity;
    bird_pos = bird_pos + bird_velocity;
    spike_x -= 0.6;
    if (spike_x < -30) {
        spike_x = 150;
        randomize_spike_height();
    }
    Circle bird(bird_pos, bird_pos + Vector(3, 1));//TODO kódduplikációó
    Polygon spike1(Vector(spike_x, 0), Vector(spike_x, 10 + spike_y_offset), 3);
    Polygon spike2(Vector(spike_x, 80), Vector(spike_x, 30 + spike_y_offset), 3);
    return (spike1.intersects_with(bird) or spike2.intersects_with(bird));
}
