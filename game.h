#ifndef GAME_H
#define GAME_H

#include "screen.h"
#include "console.h"

class Game {
public:
    virtual void input(int code) = 0;
    
    /// @return hogy vége van-e a játéknak az update miatt
    virtual bool update(double delta, Screen& screen) = 0;
    
    /// @return true, if the timer ran out, false if player died or quit
    bool play(Console& con, Screen& screen, double timeout);
};

#endif // GAME_H
