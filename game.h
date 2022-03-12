#ifndef GAME_H
#define GAME_H

class Game {
public:
    virtual void input(int code) = 0;//?? TODO
    virtual void draw_frame() = 0;
    virtual bool tick_physics(double delta) = 0; // visszaadja, hogy vége van-e a játéknak
};

#endif // GAME_H
