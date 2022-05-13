/**
 * \file main.cpp
 * A főprogram, ami a definiált makróknak megfelelően elindítja a kívánt maineket.
 */
#include "memtrace.h"

//TODO helyesírás ellenőrzés
//TODO makrómágia MAIN_GAME makróval feltételes fordítása a játékoknak + main_gamenek + consolenak
//TODO doksi képek + szöveg update
//TODO igazi dokumentáció
//TODO átnézni a pontozást
//TODO név + nkód
//TODO windows eof teszt???
//TODO 100% coverage test, assert a nem használt exceptionok helyett

#include <iostream>

#include "mains.h"

#if !defined(CPORTA) && !defined(MAIN_ASSIGNMENT) && !defined(MAIN_GAME)
#error "Please define one of the macros: CPORTA (=main_test), MAIN_ASSIGNMENT or MAIN_GAME"
#endif

int main() {
    try {
#ifdef CPORTA
        main_test();
#endif // CPORTA
#ifdef MAIN_ASSIGNMENT
        main_assignment(std::cin, std::cout);
#endif // MAIN_ASSIGNMENT
#ifdef MAIN_GAME
        main_game();
#endif // MAIN_GAME
    } catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }
}
