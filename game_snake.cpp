#include "game_snake.h"

#include <fstream>

#include "shapes.hpp"

GameSnake::GameSnake(): shape_parser(std::ifstream("snake_level.txt")), delta_since_last_jump(0), forward(Vector::RIGHT) {
    Vector pos(Screen::size.x*0.5, Screen::size.y*0.5);
    for (int i = 0; i < SNAKE_LENGTH; ++i)
        snake_pos[i] = pos + Vector::LEFT * i * block_size;
}

void GameSnake::input(int code) {
    switch (code) { // TODO wasd
        case Console::KEY_LEFT : forward = Vector::LEFT ; break;
        case Console::KEY_RIGHT: forward = Vector::RIGHT; break;
        case Console::KEY_UP   : forward = Vector::UP   ; break;
        case Console::KEY_DOWN : forward = Vector::DOWN ; break;
    }
}

bool GameSnake::update(double delta, Screen& screen) {
    delta_since_last_jump += delta;
    if (delta_since_last_jump >= seconds_till_snake_jumps) {
        delta_since_last_jump -= seconds_till_snake_jumps;
        Vector previous = snake_pos[0];
        snake_pos[0] += forward * block_size;
        for (int i = 1; i < SNAKE_LENGTH; ++i) {
            Vector tmp = snake_pos[i];
            snake_pos[i] = previous;
            previous = tmp;
        }
    }
    Polygon head(snake_pos[0], snake_pos[0] + forward * (block_size / 2.0001 * 1.1), 3);
    screen.draw_shape(head);
    Circle head_collision(snake_pos[0], snake_pos[0] + Vector(block_size / 2.0001, 0));
    bool died = false;
    for (int i = 1; i < SNAKE_LENGTH; ++i) {
        Polygon body(snake_pos[i], snake_pos[i] + Vector(block_size / 2.0001, block_size / 2.0001), 4);
        screen.draw_shape(body);
        died = died || body.intersects_with(head_collision);
    }
    for (size_t i = 0; i < shape_parser.array.len(); ++i) {
        screen.draw_shape(*shape_parser.array[i]);
        died = died || shape_parser.array[i]->intersects_with(head_collision);
    }
    //std::cout << head << *shape_parser.array[2];
    return died;
}
