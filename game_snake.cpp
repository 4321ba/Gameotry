#include "memtrace.h"

#include "game_snake.h"

#include "shapes.h"

GameSnake::GameSnake(std::istream& is): shape_parser(is), delta_since_last_jump(0), forward(Vector::RIGHT) {
    Vector pos = Screen::size * 0.5;
    for (int i = 0; i < SNAKE_LENGTH; ++i)
        snake_pos[i] = pos + Vector::LEFT * i * block_size;
}

void GameSnake::input(int code) {
    switch (code) {
        case Console::KEY_LEFT : case 'a': forward = Vector::LEFT ; break;
        case Console::KEY_RIGHT: case 'd': forward = Vector::RIGHT; break;
        case Console::KEY_UP   : case 'w': forward = Vector::UP   ; break;
        case Console::KEY_DOWN : case 's': forward = Vector::DOWN ; break;
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
    Circle head_collision(snake_pos[0], block_size / 2.0001);
    bool died = false;
    for (int i = 1; i < SNAKE_LENGTH; ++i) {
        Polygon body(snake_pos[i], snake_pos[i] + Vector(block_size / 2.0001, block_size / 2.0001), 4);
        screen.draw_shape(body);
        died = died || body.intersects_with(head_collision);
    }
    for (const Shape& s: shape_parser) {
        screen.draw_shape(s);
        died = died || s.intersects_with(head_collision);
    }
    return died;
}
