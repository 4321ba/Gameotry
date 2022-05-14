/**
 * \file shape_parser.h
 * Az alakzatbeolvasó osztály.
 * 
 * Saját dinamikus memóriáját kezeli, és felhasználja a dinamikus tömböt a pointerek tárolására.
 * Adatok elérése kizárólag iterátorral, a beolvasott adatok nem módosíthatóak.
 */
#ifndef SHAPE_PARSER_H
#define SHAPE_PARSER_H
#include "memtrace.h"

#include <iostream>
#include "dynarray.hpp"
#include "shapes.h"

/**
 * Az alakzatbeolvasó osztály.
 * 
 * Saját dinamikus memóriáját kezeli, és felhasználja a dinamikus tömböt a pointerek tárolására.
 * Adatok elérése kizárólag iterátorral, a beolvasott adatok nem módosíthatóak.
 */
class ShapeParser {
    DynArray<Shape*> array;
    typedef DynArray<Shape*>::Iterator SuperIt;
    
    ShapeParser(const ShapeParser&);
    ShapeParser& operator=(const ShapeParser&);
public:
    /// Konstruktor, és egyben beolvasó függvény is. RAII, így a konstruktorban foglalja a dinamikus memóriáját.
    /// @param pred predikátum, meg lehet mondani, hogy eltároljuk-e az adott alakzatot
    /// @param is ahonnét az alakzatokat olvassa, addig, amíg nem lesz hiba. Sikeres beolvasást is.eof()-fal lehet (és érdemes) tesztelni.
    ShapeParser(std::istream& is,
                bool (*pred)(const Shape&) = [](const Shape&) { return true; }
               );
    ~ShapeParser();
    
    // because we want to return Shape& and not Shape*& when dereferencing the iterator
    /// Azért kell külön iterátor, mert Shape&-eken akarunk iterálni, és nem Shape*&-eken.
    /// NEM JÓK AZ ÖRÖKÖLT TYPEDEFJEI! valószínűleg furcsán fog viselkedni std::algoritmusokkal, megpróbáltam letiltani.
    /// Mivel ennek nincs is value type-ja, mert a Shape absztrakt.
    class Iterator: public SuperIt {
        /// ennek nincs is value_type-ja, Shape absztrakt, megpróbálom így felülírni, hátha így nem engedi az std::algoritmusokat használni rajta
        using value_type = std::nullptr_t;
    public:
        Iterator(const SuperIt& it): SuperIt(it) { }
        const Shape& operator*() { return *SuperIt::operator*(); }
    };
    
    Iterator begin() { return array.begin(); }
    Iterator end() { return array.end(); }
};

#endif // SHAPE_PARSER_H
