// TODO helyesírás ellenőrzés
// TODO cerr használata?
// TODO and or not helyett && || !
// is és os in és out helyett (iostream)
// TODO console.cpp-ben külön opcióként szétválasztani az utf8 és cpmittoménmi kódolást, hogy windowson is lehessen tesztelni utf8-cal (tesztprogram tesztelhessen utf8 kódokkal)
// TODO átnevezni .hpp-ről .h -ra a headeröket
//TODO Console fallback implementáció standard c++-szal / vagy olyan fordítási opció ahol nincs szükség rá (makrómágia)
//TODO memtrace!

#include <iostream>

#include "mains.h"

int main() {
    try {
#ifndef MAIN_TEST // TODO n
        /*int code = */main_test();
    //     if (code != 0) {
    //         std::cerr << "Error " << code << " occured, while testing!" << std::endl;
    //         return code;
    //     }
#endif // MAIN_TEST
#ifndef MAIN_ASSIGNMENT
        main_assignment();
#endif // MAIN_ASSIGNMENT
#ifndef MAIN_GAME
        main_game();
#endif // MAIN_GAME
    } catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }
}
