#include <iostream>
using std::ostream;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include "vectormath.hpp"
#include "shapes.hpp"
#include "console.h"

#include "game_flappy_bird.h"

// https://stackoverflow.com/questions/41077377/how-to-get-current-time-in-milliseconds
// http://www.cplusplus.com/reference/chrono/
#include <chrono>
using std::chrono::nanoseconds;
using clk = std::chrono::high_resolution_clock;

int main() {
    Console& con = Console::con();
    con.clrscr();
    
    GameFlappyBird fb;
    Game& game = fb;
    
    clk::time_point previous = clk::now();
    long int fps_display_delta = 0;
    int frames = 0;
    int currfps = 0;
    bool exit = false;
    while(!exit) {
        clk::time_point now = clk::now();
        long int delta = ((nanoseconds)(now - previous)).count();
        previous = now;
        cout << "time since prev now (=delta): " << delta / 1000000.0 << endl;
        
        while (con.kbhit())
            game.input(con.getch());
        con.gotoxy(1, 1);
        exit = game.update(delta / 1000000000.0);
        ++frames;
        fps_display_delta += delta;
        
        if (fps_display_delta >= 1000000000) {
            fps_display_delta = 0;
            currfps = frames;
            frames = 0;
        }
        cout << "fps: " << currfps << endl;
        
        
    }
}

