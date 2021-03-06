/**
 * \file game_asteroids.h
 * Aszteriodák játék minimális változata.
 *
 * A játékosnak adott ideig kell túlélnie úgy, hogy egyenes vonalú egyenletes mozgással
 * menő, egyre több aszteroidát kell elkerülnie.
 * Lövés nincs, és bizonyos mennyiségű aszteroidával kezdődik a játék.
 * Az új aszteroidák a pálya szélén keletkeznek.
 * Ami kimegy az egyik oldalon, az megjelenik a másikon.
 */
#ifndef GAME_ASTEROIDS_H
#define GAME_ASTEROIDS_H
#include "memtrace.h"

#include "vectormath.h"
#include "screen.h"
#include "dynarray.hpp"
#include "game.h"

/**
 * Aszteriodák játék minimális változata.
 *
 * A játékosnak adott ideig kell túlélnie úgy, hogy egyenes vonalú egyenletes mozgással
 * menő, egyre több aszteroidát kell elkerülnie.
 * Lövés nincs, és bizonyos mennyiségű aszteroidával kezdődik a játék.
 * Az új aszteroidák a pálya szélén keletkeznek.
 * Ami kimegy az egyik oldalon, az megjelenik a másikon.
 */
class GameAsteroids: public Game {
    constexpr static double acceleration = 4; // pixel/s / button pressed
    constexpr static double seconds_until_asteroid = 4.0;
    
    /// itt az enkapszuláció nagyobb szinten történik: a GameAsteroids szintjén, ezért nem figyel az Actor magára (publikus tagváltozók, kevés tagfüggvény)
    /// inkább nem duzzasztom fel a kódot get_rot(), set_rot(), stb. boilerplate-tel, minél kevesebb kód, annál kevesebb hibalehetőség
    /// hasonlóan felduzzasztaná a kódot egy-egy játékos, illetve aszteroida alosztály létrehozása, és a több, bonyolultabb kód miatt még kevésbé is tudnám érteni, nehezebb lenne követni a (részben virtuális) függvényhívások tömkelegét, pl a kirajzoláshoz vagy a hozzá tartozó Shape lekérdezéséhez, amikor egyszerűbben meg lehet oldani ezek nélkül
    struct Actor {
        Vector pos, speed;
        double size;
        double rot;
        /// inicializáció memóriaszeméttel, a DynArray-hoz kell, ahol az elemek úgyis érvénytelenek
        Actor() { }
        Actor(Vector p, Vector s, double sz): pos(p), speed(s), size(sz), rot(0) { }
        void update(double delta);
    };
    
    Actor player;
    DynArray<Actor> asteroids;
    double seconds_since_asteroid;
    
    /// mindig a pálya szélén idéz
    void spawn_random_asteroid();
public:
    GameAsteroids();
    void input(int code);
    bool update(double delta, Screen& screen);
};

#endif // GAME_ASTEROIDS_H
