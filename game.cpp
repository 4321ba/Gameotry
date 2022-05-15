/**
 * \file game.cpp
 * Minden játék főciklusa, általánosítva.
 */
#ifdef MAIN_GAME
#include "memtrace.h"

#include <iostream>
#include <ctime>
#include "game.h"

const double max_delta = 0.1/*sec*/;

/// Minden játék főciklusa, általánosítva.
bool Game::play(Console& con, Screen& screen, double timeout) {
    clock_t previous = clock();
    double game_timeout_delta = 0.0;
    double fps_display_delta = 0.0;
    int counted_frames = 0;
    int displayed_fps = 0;
    bool quit = false;
    while(!quit) {
        clock_t now = clock();
        double delta = (double)(now - previous) / CLOCKS_PER_SEC;
        if (delta > max_delta)
            delta = max_delta;
        previous = now;
        
        while (con.kbhit()) {
            int c = con.getch();
            if (c == 'q')
                quit = true;
            else
                this->input(c);
        }
        
        con.gotoxy(1, 1);
        screen.clear();
        quit = this->update(delta, screen) || quit;
        std::cout << screen;
        std::cout << "Remaining time: " << timeout - game_timeout_delta
                  << ", fps: " << displayed_fps
                  << ", mspt: " << 1000.0 * delta
                  << "   " << std::flush;
        
        ++counted_frames;
        fps_display_delta += delta;
        if (fps_display_delta >= 1.0) {
            fps_display_delta -= 1.0;
            displayed_fps = counted_frames;
            counted_frames = 0;
        }
        game_timeout_delta += delta;
        if (game_timeout_delta >= timeout)
            break;
        
    }
    con.clrscr();
    con.gotoxy(1, 1);
    return !quit;
}

#endif // MAIN_GAME
