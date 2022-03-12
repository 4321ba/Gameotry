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
#include <cstdlib>//for random

int main() {
    srand(time(NULL));

    Console& con = Console::con();
    con.clrscr();
    
    GameFlappyBird fb;
    Game& game = fb;
    
    clk::time_point previous = clk::now();
    clk::time_point previousfps = previous;
    long int remainder = 0; // nanoseconds for physics update remaining from before last frame
    long int prevvait = 0;
    int frames = 0;
    int currfps = 0;
    bool exit = false;
    while(!exit) {
        /*
        while (con.kbhit())
            game.input(con.getch());
        
        constexpr long int physics_fps = 60; // tick per second
        constexpr long int nspt = 1000000000 / physics_fps; // nanosecond per tick
        
        clk::time_point now = clk::now();
        long int ns_delta = (now - previous).count();
        previous = now;
        long int physics_delta = ns_delta + remainder;
        remainder = physics_delta % nspt;
        
        for (int i = 0; i < physics_delta / nspt; ++i) {
            exit = game.tick_physics(1.0 / physics_fps);
            cout <<"            \r" << i;
        }
        
        con.gotoxy(1, 1);
        game.draw_frame();
        if (ns_delta - nspt > 0)
            sleep_for(nanoseconds(ns_delta - nspt));
        */
        
        
        
        
        
        
        
        
        constexpr long int fps = 60;
        constexpr long int max_nspt = 1000000000 / fps;
        while (con.kbhit())
            game.input(con.getch());
        
        for (int i = 0; i < remainder / max_nspt and not exit; ++i)
            exit = game.tick_physics(1.0);
        remainder %= max_nspt;
        
        con.gotoxy(1, 1);
        game.draw_frame();
        ++frames;
        
        clk::time_point now = clk::now();
        nanoseconds delta = now - previous;
        previous = now;
        cout << "time since prev now: " << delta.count() / 1000000.0 << endl;
        
        if (((nanoseconds)(now - previousfps)).count() > 1000000000.0) {
            previousfps = now;
            currfps = frames;
            frames = 0;
        }
        cout << "fps: " << currfps << endl;
        
        
        nanoseconds wait = nanoseconds(max_nspt + prevvait) - delta;
        prevvait = wait.count();
        cout << "waiting for this long: " << prevvait / 1000000.0 << endl;
        
        
        if (prevvait > 0)
            sleep_for(nanoseconds(prevvait));
        remainder += prevvait > 0 ? max_nspt : delta.count();
        //remainder += delta.count();
        
        
        
        
    }
}

