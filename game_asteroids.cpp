#include "memtrace.h"

#include "game_asteroids.h"

#include <cstdlib>

#include "shapes.h"

namespace {
    double randd(double range) { return range * rand() / RAND_MAX; }
}

void GameAsteroids::spawn_random_asteroid() {
    Vector pos;
    // oldal sorsolása a 4 közül, fent-lent / jobbra-balra között a sebesség tesz majd különbséget
    if (randd(1.0) < 0.5)
        pos = Vector(randd(Screen::size.x), 0);
    else
        pos = Vector(0, randd(Screen::size.y));
    Vector speed = Vector::polar(randd(4) + 3, randd(MATH_PI * 2));
    asteroids.append(Actor(pos, speed, 1 + randd(2)));
}

void GameAsteroids::Actor::update(double delta) {
    pos += speed * delta;
    if (pos.x < 0)
        pos.x += Screen::size.x;
    else if (pos.x > Screen::size.x)
        pos.x -= Screen::size.x;
    if (pos.y < 0)
        pos.y += Screen::size.y;
    else if (pos.y > Screen::size.y)
        pos.y -= Screen::size.y;
}


GameAsteroids::GameAsteroids():
    player(Screen::size * 0.5, Vector(0, 0), 4), seconds_since_asteroid(0) {
    spawn_random_asteroid();
    spawn_random_asteroid();
    spawn_random_asteroid();
    spawn_random_asteroid();
}

void GameAsteroids::input(int code) {
    switch (code) {
        case Console::KEY_LEFT:
        case 'a':
            player.rot -= MATH_PI / 4; break;
        case Console::KEY_RIGHT:
        case 'd':
            player.rot += MATH_PI / 4; break;
        case Console::KEY_UP:
        case 'w':
            player.speed += Vector::polar(acceleration, player.rot); break;
    }
}

bool GameAsteroids::update(double delta, Screen& screen) {
    player.update(delta);
    Vector nose_pos = player.pos + Vector::polar(player.size, player.rot);
    Polygon player_body(player.pos, nose_pos, 3);
    Circle player_head(nose_pos, 1);
    screen.draw_shape(player_body);
    screen.draw_shape(player_head);
    
    seconds_since_asteroid += delta;
    if (seconds_since_asteroid >= seconds_until_asteroid) {
        seconds_since_asteroid -= seconds_until_asteroid;
        spawn_random_asteroid();
    }
    bool collided = false;
    for (Actor& asteroid: asteroids) {
        asteroid.update(delta);
        Circle c(asteroid.pos, asteroid.size);
        collided = collided || player_body.intersects_with(c) || player_head.intersects_with(c);
        screen.draw_shape(c);
    }
    return collided;
}
