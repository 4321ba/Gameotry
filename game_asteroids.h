#ifndef GAME_ASTEROIDS_H
#define GAME_ASTEROIDS_H

#include "vectormath.h"
#include "screen.h"
#include "dynarray.hpp"
#include "game.h"

class GameAsteroids: public Game { // TODO többi class static változóját is konzisztensen
    constexpr static double acceleration = 4; // pixel/s / button pressed
    constexpr static double seconds_until_asteroid = 4.0;
    
    // itt az enkapszuláció nagyobb szinten történik: a GameAsteroids szintjén, ezért nem figyel az Actor magára (publikus tagváltozók, kevés tagfüggvény)
    // fölösleges volna felduzzasztani a kódot get_rot(), set_rot(), stb. boilerplate-tel, minél kevesebb kód, annál kevesebb hibalehetőség
    // hasonlóan felduzzasztaná a kódot egy-egy játékos, illetve aszteroida alosztály létrehozása, és a több, bonyolultabb kód miatt még kevésbé is volna olvasható, nehezebb lenne követni a (részben virtuális) függvényhívások tömkelegét, pl a kirajzoláshoz vagy a hozzá tartozó Shape lekérdezéséhez, amikor egyszerűbben és szebben meg lehet oldani ezek nélkül
    struct Actor {
        Vector pos, speed;
        double size;
        double rot;
        Actor() { } // inicializáció memóriaszeméttel, miért lenne speciálisabb az origó, mint a (42, 69) pont?
        // az inicializálatlan változók a megfelelő érték hiányára utalnak (tünet), tehát a megfelelő helyen, megfelelő értékkel történő értékadással kell kiküszöbölni (pl tömbelem), nem logikátlan érték adásával a default construktorban // TODO finomítani
        Actor(Vector p, Vector s, double sz): pos(p), speed(s), size(sz), rot(0) { }
        void update(double delta);
    };
    
    Actor player;
    DynArray<Actor> asteroids;
    double seconds_since_asteroid;
    
    // mindig a pálya szélén idéz:
    void spawn_random_asteroid();
public:
    GameAsteroids();
    void input(int code);
    bool update(double delta, Screen& screen);
};

#endif // GAME_ASTEROIDS_H
