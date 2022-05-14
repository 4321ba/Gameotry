/**
 * \file screen.h
 * Az alakzatok lerendereléséért felelős osztály.
 * 
 * Az alakzatok has_point függvényét hívogatva készít egy képet, amit képes kiírni egy kimeneti folyamra.
 */
#ifndef SCREEN_H
#define SCREEN_H
#include "memtrace.h"

#include <iostream>
#include "shapes.h"

/**
 * Az alakzatok lerendereléséért felelős osztály.
 * Egy pixel 2 értéket vehet fel, tehát fekete-fehér a kép.
 */
class Screen {
    const unsigned width, height;
    bool* data;
    
    bool& idx(unsigned x, unsigned y);
    bool idx(unsigned x, unsigned y) const;
    
    /// we don't allow these
    Screen(const Screen&);
    Screen& operator=(const Screen&);
public:
    /// A képernyő rajzoláskor ekkorának néz ki, azért, hogy felbontásfüggetlen legyen.
    /// Tehát például a (40,25) középpontú kör mindig a képernyő közepén lesz, függetlenül a konzol felbontásától.
    static const Vector size;
    
    /// A paraméterek a terminál felbontására vonatkoznak, tehát például egy 100 oszlopú, 20 sorú konzolablakra
    /// width=100, height=40 -es Screen-t kell készíteni, ha azt akarjuk, hogy az egészet éppen befedje
    /// A magasságot amiatt kell duplázni, mert egy karakter (doboz) 2 pixelnek felel meg (szóköz, alsó doboz, felső doboz vagy teljes doboz)
    /// A magasság 2-vel oszthatóvá lesz téve emiatt
    Screen(unsigned width, unsigned height);
    ~Screen() { delete[] data; }
    
    /// A bufferbe belerajzolja az alakzatot, figyelembe véve a virtuális és az igazi felbontás közötti összefüggést.
    /// Lehet egymás után több alakzatot is rajzolni, ezek átfedésénél a határt közöttük utólag nem lehet megkülönböztetni.
    void draw_shape(const Shape& s);
    
    /// Kiírja a buffert az adatfolyamra.
    void render(std::ostream& out) const;
    
    /// Törli a buffer minden pixelét.
    void clear();
};

inline std::ostream& operator<<(std::ostream& out, const Screen& s) {
    s.render(out);
    return out;
}

#endif // SCREEN_H
