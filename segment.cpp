/**
 * \file segment.cpp
 * A szakasz tagfüggvényei, síkgeometria / koordinátageometria.
 */
#include "memtrace.h"

#include "segment.h"

// visszaadja, hogy bal oldalon van-e a pont, amennyiben a pozitív forgásirány
// óramutató járásával ellenkező (azaz +y felfelé van)
// ha óramutatóval megegyező / +y lefelé van (pl képernyő),
// akkor azt mondja meg, hogy jobbra van-e a pont
bool Segment::is_point_to_the_left(Vector p) const {
    // https://stackoverflow.com/questions/1560492/how-to-tell-whether-a-point-is-to-the-right-or-left-side-of-a-line
    Vector ab = b - a;
    Vector ap = p - a;
    // az egyik különbségvektor normálása, majd a skalárszorzat előjele megmondja
    return ab.x * ap.y - ab.y * ap.x > 0;
}

// visszaadja, hogy a szakasz mely pontja van `p`-hez legközelebb
// a visszatérési pont mindig a szakaszon van, azaz mindig `a` és `b` között
Vector Segment::closest_point_to(Vector p) const {
    // https://stackoverflow.com/questions/3120357/get-closest-point-to-a-line
    Vector ab = b - a;
    Vector ap = p - a;
    double dot = ab * ap; // = |ab| * |ap| * cos bezártszög = |ap vetülete| * |ab|
    double ab_length_squared = a.distance_squared_to(b); // = |ab|²
    double lerp_weight = dot / ab_length_squared; // = |ap vetülete| / |ab|
    if (lerp_weight <= 0)
        return a;
    if (lerp_weight >= 1)
        return b;
    return a + ab * lerp_weight;
}
