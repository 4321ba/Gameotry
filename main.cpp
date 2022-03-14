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

const double SECONDS_PER_GAME = 10.0;

// @return true, if the timer ran out, false if player died or quit
bool play_game(Game& game, Console& con) {
    clock_t previous = clock();
    double game_timeout_delta = 0.0;
    double fps_display_delta = 0.0;
    int counted_frames = 0;
    int displayed_fps = 0;
    bool quit = false;
    while(!quit) {
        clock_t now = clock();
        double delta = (double)(now - previous) / CLOCKS_PER_SEC;
        previous = now;
        
        while (con.kbhit()) {
            int c = con.getch();
            if (c == 'q')
                quit = true;
            else
                game.input(c);
        }
        
        con.gotoxy(1, 1);
        quit = game.update(delta) || quit;
        cout << "fps: " << displayed_fps << ", mspt: " << 1000.0 * delta << flush;
        
        ++counted_frames;
        fps_display_delta += delta;
        if (fps_display_delta >= 1.0) {
            fps_display_delta = 0.0;
            displayed_fps = counted_frames;
            counted_frames = 0;
        }
        game_timeout_delta += delta;
        if (game_timeout_delta >= SECONDS_PER_GAME)
            break;
        
    }
    con.clrscr();
    con.gotoxy(1, 1);
    return !quit;
}

int main() {
    Console& con = Console::con();
    con.clrscr();
    
    GameFlappyBird fb;
    bool success = play_game(fb, con);
    cout << (success ? "Success!" : "Failure...") << endl;
}

