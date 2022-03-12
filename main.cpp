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

// https://www.cplusplus.com/reference/thread/this_thread/sleep_for/
// https://stackoverflow.com/questions/41077377/how-to-get-current-time-in-milliseconds
// http://www.cplusplus.com/reference/chrono/
#include <thread>
#include <chrono>
using std::this_thread::sleep_for;
using std::chrono::nanoseconds;
using clk = std::chrono::high_resolution_clock;

int main() {

    Console& con = Console::con();
    con.clrscr();
    
    GameFlappyBird fb;
    Game& game = fb;
    
    clk::time_point previous = clk::now();
    clk::time_point previousfps = previous;
    long int wait = 0;
    int frames = 0;
    int currfps = 0;
    bool exit = false;
    while(!exit) {
        
        constexpr long int fps = 60;
        constexpr long int max_nspt = 1000000000 / fps;
        
        clk::time_point now = clk::now();
        long int delta = ((nanoseconds)(now - previous)).count();
        previous = now;
        cout << "time since prev now (=delta): " << delta / 1000000.0 << endl;
        
        while (con.kbhit())
            game.input(con.getch());
        con.gotoxy(1, 1);
        double passed_delta = wait > 0 ? 1.0 / fps : delta / 1000000000.0;
        exit = game.update(passed_delta);
        ++frames;
        
        
        
        
        if (((nanoseconds)(now - previousfps)).count() > 1000000000.0) {
            previousfps = now;
            currfps = frames;
            frames = 0;
        }
        cout << "fps: " << currfps << endl;
        
        
        wait = max_nspt - (delta - /*previous*/wait);
        wait = wait > 0 ? wait : 0;
        cout << "waiting for this long: " << wait / 1000000.0 <<"                    "<< endl;
        
        
        if (wait > 0)
            sleep_for(nanoseconds(wait));
        
        
    }
}

