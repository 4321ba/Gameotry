#ifndef GAME_H
#define GAME_H
#include "memtrace.h"

#include "screen.h"
#include "console.h"

class Game {
public:
    virtual void input(int code) = 0;
    
    /// @return hogy vége van-e a játéknak az update miatt
    virtual bool update(double delta, Screen& screen) = 0;
    
    /// @return igaz, ha az idő lejárt, hamis, ha a játékos meghalt, vagy kilépett
    bool play(Console& con, Screen& screen, double timeout);
    
    virtual ~Game() { }
};

#endif // GAME_H
