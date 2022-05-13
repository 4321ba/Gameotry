/**
 * \file game_flappy_bird.h
 * Minimális Flappy Bird implementáció.
 * 
 * A játékos nem érhet hozzá a plafonhoz, sem a padlóhoz, sem a tüskékhez.
 * Egyszerre mindig két tüske van a képernyőn, egy fent, egy lent,
 * ezek egyenletesen mozognak jobbról balra.
 * A lyuk magassága valamennyire véletlenszerű, de a mérete állandó.
 */
#ifndef GAME_FLAPPY_BIRD_H
#define GAME_FLAPPY_BIRD_H
#include "memtrace.h"

#include "vectormath.h"
#include "screen.h"
#include "game.h"

/**
 * Minimális Flappy Bird implementáció.
 * 
 * A játékos nem érhet hozzá a plafonhoz, sem a padlóhoz, sem a tüskékhez.
 * Egyszerre mindig két tüske van a képernyőn, egy fent, egy lent,
 * ezek egyenletesen mozognak jobbról balra.
 * A lyuk magassága valamennyire véletlenszerű, de a mérete állandó.
 */
class GameFlappyBird: public Game {
    const Vector gravity = Vector(0, 40); // block per sec^2
    const Vector jump_speed = Vector(0, -32); // block per sec
    const double spike_x_speed = -45; // block per sec
    const Polygon upper_wall = Polygon(Vector(Screen::size.x / 2, Screen::size.y*0.01 - Screen::size.x / 2), Vector(0, Screen::size.y*0.01), 4);
    const Polygon lower_wall = Polygon(Vector(Screen::size.x / 2, Screen::size.y*0.99 + Screen::size.x / 2), Vector(0, Screen::size.y*0.99), 4);
    
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
