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
// TODO console.cpp-ben külön opcióként szétválasztani az utf8 és cpmittoménmi kódolást, hogy windowson is lehessen tesztelni utf8-cal
#include <ctime>
#include <cstdlib> // for random

#include <fstream>

#include "vectormath.hpp"
#include "shapes.hpp"
#include "console.h"
#include "shape_parser.h"

#include "game_flappy_bird.h"
#include "game_snake.h"

const double SECONDS_PER_GAME = 20.0;

#define READ_FILE // kikommentelendő? TODO: külön fájlba + 3. fájl a teszt

#ifndef READ_FILE
int main() {
    srand(time(NULL));
    Console& con = Console::con();
    con.clrscr();
    
    int width = 80, height = 25;
    con.getsize(width, height);
    Screen screen(width, 2 * (height - 1/*for fps count*/));
//     GameFlappyBird game;
    GameSnake game;
    bool success = game.play(con, screen, SECONDS_PER_GAME);
    cout << (success ? "Success!" : "Failure...") << endl;
}

#else
int main() {
    std::ifstream f("snake_level.txt");
    ShapeParser p(std::move(f));//TODO ellenőrzés??
    
    for (size_t i = 0; i < p.array.len(); ++i)
        cout << *p.array[i] << endl;
    
    
    //for (size_t i = 0; i < p.array.len(); ++i)
    //    screen.draw_shape(*p.array[i]);
    //cout << screen;
}
#endif
