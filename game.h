/**
 * \file game.h
 * Absztrakt játék alaposztály, a közösen kezelhetőség céljából.
 */
#ifndef GAME_H
#define GAME_H
#include "memtrace.h"

#include "screen.h"
#include "console.h"

/**
 * Absztrakt játék alaposztály, a közösen kezelhetőség céljából.
 * 
 * Meghívódik az update függvénye, ha frissíteni lehet a képet, és az input függvénye, ha bemenet érkezett. Ezeket kell felülírni, a play-t nem.
 */
class Game {
public:
    virtual void input(int code) = 0;
    
    /// @param delta az eltelt idő, másodpercben
    /// @param screen amire rajzolni kell
    /// @return hogy vége van-e a játéknak az update miatt
    virtual bool update(double delta, Screen& screen) = 0;
    
    /// @return igaz, ha az idő lejárt, hamis, ha a játékos meghalt, vagy kilépett
    bool play(Console& con, Screen& screen, double timeout);
    
    virtual ~Game() { }
};

#endif // GAME_H
