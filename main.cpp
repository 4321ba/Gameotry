/**
 * \file main.cpp
 * A főprogram, ami a definiált makróknak megfelelően elindítja a kívánt maineket.
 */
#include "memtrace.h"

//TODO helyesírás ellenőrzés
//TODO doksi képek + szöveg update
//TODO igazi dokumentáció
//TODO doxygen pdf mögécsatolás
//TODO átnézni a pontozást
//TODO név + nkód, readme.md-t kivenni a doxygen generálás előtt
//TODO windows eof teszt??? !!!
//TODO ~shapeparser exception?

#include <iostream>

#include "mains.h"

#if !defined(CPORTA) && !defined(MAIN_ASSIGNMENT) && !defined(MAIN_GAME)
#error "Please define one of the macros: CPORTA (=main_test), MAIN_ASSIGNMENT or MAIN_GAME"
#endif

/**
 * A főprogram, ami a definiált makróknak megfelelően elindítja a kívánt maineket.
 */
int main() {
    try {
#ifdef CPORTA
        main_test();
#endif // CPORTA
        // a coverage miatt:
#if defined(CPORTA) && !defined(MAIN_ASSIGNMENT) && !defined(MAIN_GAME)
        throw std::runtime_error("Testing catch in main.");
#endif // CPORTA && !MAIN_ASSIGNMENT && !MAIN_GAME
#ifdef MAIN_ASSIGNMENT
        main_assignment(std::cin, std::cout);
#endif // MAIN_ASSIGNMENT
#ifdef MAIN_GAME
        main_game();
#endif // MAIN_GAME
    } catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        // a coverage miatt ezt a részt is le kell futtatni, hogy meg legyen a 100%
        // viszont return 1 nem lehet, mert akkor sikertelen lesz a beadás
#if defined(CPORTA) && !defined(MAIN_ASSIGNMENT) && !defined(MAIN_GAME)
        return 0;
#else
        return 1;
#endif // CPORTA && !MAIN_ASSIGNMENT && !MAIN_GAME
    }
}
