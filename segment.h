/**
 * \file segment.h
 * A szakasz, ami izomorf 2db 2 dimenziós ponttal, megvalósítása.
 * Hasznos a sokszög oldalához; ahhoz, hogy egy pont az oldalon belül van-e, illetve a körrel való metszés meghatározására.
 */
#ifndef SEGMENT_H
#define SEGMENT_H
#include "memtrace.h"

#include <iostream>
#include <exception>

#include "vector.h"

// represents a segment, or a line
struct Segment {
    Vector a, b; // 2 endpoints
    Segment(Vector a, Vector b): a(a), b(b) {
        if (a.x == b.x && a.y == b.y)
            throw std::logic_error("2 endpoints of a segment cannot be the same!");
    }
    
    // visszaadja, hogy bal oldalon van-e a pont, amennyiben a pozitív forgásirány
    // óramutató járásával ellenkező (azaz +y felfelé van)
    // ha óramutatóval megegyező / +y lefelé van (pl képernyő),
    // akkor azt mondja meg, hogy jobbra van-e a pont
    bool is_point_to_the_left(Vector p) const;
    
    // result is between a and b
    // visszaadja, hogy a szakasz mely pontja van `p`-hez legközelebb
    // a visszatérési pont mindig a szakaszon van, azaz mindig `a` és `b` között
    Vector closest_point_to(Vector p) const;
};

inline std::ostream& operator<<(std::ostream& out, const Segment& s) {
    return out << "Segment(" << s.a << ", " << s.b << ")";
}

#endif // SEGMENT_H
