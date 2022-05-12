#include "memtrace.h"

//TODO helyesírás ellenőrzés
//TODO makrómágia MAIN_GAME makróval feltételes fordítása a játékoknak + consolenak
//TODO külön cpp és h minden osztályhoz!
//TODO doksi képek + szöveg update
//TODO átnézni a pontozást
//TODO clang checkvmi
//TODO név + nkód
//TODO -fsanitize=address

#include <iostream>

#include "mains.h"

#if !defined(CPORTA) && !defined(MAIN_ASSIGNMENT) && !defined(MAIN_GAME)
#error "Please define one of the macros: CPORTA (=main_test), MAIN_ASSIGNMENT or MAIN_GAME"
#endif

int main() {
    try {
#ifdef CPORTA // TODO n
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
