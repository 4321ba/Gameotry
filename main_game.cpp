/**
 * \file main_game.cpp
 * A játékprogramok futtatásáért felelős főprogram.
 * 
 * Csak akkor fordul bele, ha a MAIN_GAME makró definiált.
 */
#ifdef MAIN_GAME
#include "memtrace.h"

#include <iostream>
#include <fstream>

// for random:
#include <ctime>
#include <cstdlib>

#include "console.h"
#include "game_flappy_bird.h"
#include "game_snake.h"
#include "game_asteroids.h"

/**
 * A játékprogramok futtatásáért felelős főprogram.
 * 
 * A 3 játék közül véletlenszerűen választ minden alkalommal, és minden játék addig tart,
 * amíg a játékos meghal, vagy 20s letelik.
 * Ha az idő letelt, akkor új játék indul. Meghaláskor a játszott játékok számát kiírja.
 * A kilépés (q gomb) meghalásnak számít.
 */
void main_game() {
    srand(time(NULL));
    Console& con = Console::con();
    con.clrscr();
    
    int width = 80;
    int height = 25;
    con.getsize(width, height);
    Screen screen(width, 2 * (height - 1/*for displaying fps count*/));
    
    bool success = true;
    unsigned games_played = 0;
    while (success) {
        Game* game;
        double random = 3.0 * rand() / RAND_MAX;
        if (random < 1)
            game = new GameFlappyBird();
        else if (random < 2)
            game = new GameAsteroids();
        else {
            std::ifstream is("snake_level.txt");
            game = new GameSnake(is);
            if (!is.eof())
                throw std::runtime_error("Missing file, or invalid input format in snake_level.txt!");
        }
        const double SECONDS_PER_GAME = 20.0;
        success = game->play(con, screen, SECONDS_PER_GAME);
        delete game;
        ++games_played;
    }
    std::cout << "You died during your " << games_played << ". game. Congratulations!" << std::endl;
}

#endif // MAIN_GAME
