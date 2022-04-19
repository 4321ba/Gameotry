#include <iostream>
using std::ostream;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::flush;
// TODO cerr használata?
// TODO and or not helyett && || !
// operator >> helyett operator>>
// is és os in és out helyett (iostream)
// TODO console.cpp-ben külön opcióként szétválasztani az utf8 és cpmittoménmi kódolást, hogy windowson is lehessen tesztelni utf8-cal (tesztprogram tesztelhessen utf8 kódokkal)
// TODO átnevezni .hpp-ről .h -ra a headeröket
//TODO Console fallback implementáció standard c++-szal / vagy olyan fordítási opció ahol nincs szükség rá (makrómágia)
#include <ctime>
#include <cstdlib> // for random

#include <fstream>

#include "vectormath.hpp"
#include "shapes.hpp"
#include "console.h"
#include "shape_parser.h"

#include "game_flappy_bird.h"
#include "game_snake.h"
#include "game_asteroids.h"


//#define READ_FILE // kikommentelendő? TODO: külön fájlba + 3. fájl a teszt

#ifndef READ_FILE
const double SECONDS_PER_GAME = 20.0;
int main() {
    srand(time(NULL));
    Console& con = Console::con();
    con.clrscr();
    
    int width = 80, height = 25;
    con.getsize(width, height);
    Screen screen(width, 2 * (height - 1/*for displaying fps count*/));
//     GameFlappyBird game;
    std::ifstream snl("snake_level.txt");
   GameSnake game(snl);
    if (!snl.eof())
        return 1;
//     GameAsteroids game;
    bool success = game.play(con, screen, SECONDS_PER_GAME);
    cout << (success ? "Success!" : "Failure...") << endl;
}

#else

bool outside_of_unit_circle(const Shape& s) {
    return !s.intersects_with(Circle(Vector(0, 0), 1.0));
}

int main() {
    const char* filename = "snake_level.txt";
    std::ifstream is(filename);
    ShapeParser p(is, outside_of_unit_circle);
    if (!is.eof()) {
        cerr << "Invalid input format in file " << filename << endl;
        return 1;
    }
    
    for (const Shape& s: p)
        cout << s << endl;
}
#endif
