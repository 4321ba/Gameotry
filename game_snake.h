/**
 * \file game_snake.h
 * Minimális Snake játék implementáció.
 * 
 * A játékos fix (10) hosszú, és ez nem változik a játék időtartama alatt.
 * A cél túlélni a kitűzött időtartamig (20s alapértelmezetten).
 * Lebegőpontos számolás és kirajzolás miatt alacsony felbontásnál zavaró lehet, hogy
 * a négyzetek oldalmérete között lehet egy-egy pixel eltérés.
 * A pályát úgy csináltam, hogy elég sok hely legyen az akadályok
 * (egy kör, egy háromszög és egy hatszög), és a 4 fal között, ahol úgy látszik, hogy
 * a kígyó el fog férni, ott tényleg el is fog.
 * A kígyó fejét jelző háromszög mindig az aktuális menetirányba mutat, de lépni csak
 * bizonyos időközönként lép. Emiatt ha a kígyó 180°-ot akarna fordulni, még a
 * következő ugrásig „vissza lehet vonni” a lépést.
 */
#ifndef GAME_SNAKE_H
#define GAME_SNAKE_H
#include "memtrace.h"

#include "vectormath.h"
#include "screen.h"
#include "shape_parser.h"
#include "game.h"

/**
 * Minimális Snake játék implementáció.
 * 
 * A játékos fix (10) hosszú, és ez nem változik a játék időtartama alatt.
 * A cél túlélni a kitűzött időtartamig (20s alapértelmezetten).
 * Lebegőpontos számolás és kirajzolás miatt alacsony felbontásnál zavaró lehet, hogy
 * a négyzetek oldalmérete között lehet egy-egy pixel eltérés.
 * A pályát úgy csináltam, hogy elég sok hely legyen az akadályok
 * (egy kör, egy háromszög és egy hatszög), és a 4 fal között, ahol úgy látszik, hogy
 * a kígyó el fog férni, ott tényleg el is fog.
 * A kígyó fejét jelző háromszög mindig az aktuális menetirányba mutat, de lépni csak
 * bizonyos időközönként lép. Emiatt ha a kígyó 180°-ot akarna fordulni, még a
 * következő ugrásig „vissza lehet vonni” a lépést.
 */
class GameSnake: public Game {
    const double seconds_till_snake_jumps = 0.2; // second per jump
    const double block_size = 4.15; // 12×19 with the std resolution of 50×80
    static const int SNAKE_LENGTH = 10;
    
    ShapeParser shape_parser;
    double delta_since_last_jump;
    Vector snake_pos[SNAKE_LENGTH];
    Vector forward;
    
public:
    GameSnake(std::istream& is);
    void input(int code);
    bool update(double delta, Screen& screen);
};

#endif // GAME_SNAKE_H
