/**
 * \file shape.cpp
 * Absztrakt síkidom ősosztály.
 * 
 * Az implementálók képesek megmondani, hogy egy pont bennük van-e, körrel érintkeznek-e,
 * illetve félig képesek perzisztens viselkedésre, bár a kiírás és a beolvasás formátuma a feladat kiírásának megfelelően nem azonos.
 */
#ifndef SHAPE_H
#define SHAPE_H
#include "memtrace.h"

#include <iostream>
#include "vectormath.h"

class Circle;

/// Absztrakt síkidom ősosztály.
class Shape {
public:
    
    /// Visszaadja, hogy a síkidomban benne van-e p pont.
    virtual bool has_point(Vector p) const = 0;
    
    /// Visszaadja, hogy a síkidomnak és c-nek van-e közös pontja (= metszik-e egymást).
    virtual bool intersects_with(const Circle& c) const = 0;
    
    // consumes 4 doubles if it can: center.x, center.y, vertex.x, vertex.y
    /// Beolvassa a síkidomot a bemeneti folyamról, 4 double (center x,y és vertex x,y) formájában.
    virtual void read_from(std::istream& is) = 0;
    
    /// Kiírja a síkidomot a kimeneti folyamra, emberileg olvasható formában, tehát ez nem alkalmazható a read_from-mal közvetlenül perzisztens viselkedés megvalósítására. (A feladat nem is kért ilyet.)
    virtual void print_to(std::ostream& os) const = 0;
    virtual ~Shape() {}
};

inline std::istream& operator>>(std::istream& is, Shape& s) {
    s.read_from(is);
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Shape& s) {
    s.print_to(os);
    return os;
}

#endif // SHAPE_H
