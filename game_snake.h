#ifndef GAME_SNAKE_H
#define GAME_SNAKE_H

#include "vectormath.h"
#include "screen.h"
#include "shape_parser.h"
#include "game.h"

class GameSnake: public Game {
    const double seconds_till_snake_jumps = 0.2; // second per jump  //TODO game.cpp-ben egyeztetni a max_delta-val
    const double block_size = 4.15; // 12×19 with the std resolution of 50×80
    static const int SNAKE_LENGTH = 10;
    
    ShapeParser shape_parser;
    double delta_since_last_jump;
    Vector snake_pos[SNAKE_LENGTH];//TODO kígyó nőjön, dintömbnek legyen haszna
    Vector forward;
    
public:
    GameSnake(std::istream& is);
    void input(int code);
    bool update(double delta, Screen& screen);
};

#endif // GAME_SNAKE_H
