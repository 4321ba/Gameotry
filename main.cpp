#include <iostream>
using std::ostream;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::flush;

#include <ctime>

#include "vectormath.hpp"
#include "shapes.hpp"
#include "console.h"

#include "game_flappy_bird.h"


int main() {
    Console& con = Console::con();
    con.clrscr();
    
    GameFlappyBird fb;
    Game& game = fb;
    
    clock_t previous = clock();
    long int fps_display_delta = 0;
    int counted_frames = 0;
    int displayed_fps = 0;
    bool exit = false;
    while(!exit) {
        clock_t now = clock();
        long int delta = now - previous;
        previous = now;
        double delta_sec = (double)delta / CLOCKS_PER_SEC;
        
        while (con.kbhit()) {
            int c = con.getch();
            if (c == 'q') exit = true;
            else game.input(c);
        }
        
        con.gotoxy(1, 1);
        exit = game.update(delta_sec) || exit;
        
        ++counted_frames;
        fps_display_delta += delta;
        if (fps_display_delta >= CLOCKS_PER_SEC) {
            fps_display_delta = 0;
            displayed_fps = counted_frames;
            counted_frames = 0;
        }
        
        cout << "fps: " << displayed_fps << ", mspt: " << 1000.0 * delta_sec << flush;
    }
    con.clrscr();
    con.gotoxy(1, 1);
}

