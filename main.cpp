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
#include <ctime>
#include <cstdlib> // for random

#include <fstream>

#include "vectormath.hpp"
#include "shapes.hpp"
#include "console.h"
#include "shape_parser.h"

#include "game_flappy_bird.h"

const double SECONDS_PER_GAME = 10.0;

int main() {
    srand(time(NULL));
    Console& con = Console::con();
    con.clrscr();
    
    int width = 80, height = 25;
    con.getsize(width, height);
    Screen screen(width, 2 * (height - 1/*for fps count*/));
    GameFlappyBird fb;
    bool success = fb.play(con, screen, SECONDS_PER_GAME);
    cout << (success ? "Success!" : "Failure...") << endl;
    
//     std::ifstream f("snake_level.txt");
//     ShapeParser p(f);
//     for (size_t i = 0; i < p.array.len(); ++i)
//         screen.draw_shape(*p.array[i]);
//     cout << screen;
}

