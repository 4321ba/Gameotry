/**
 * \file shape_polygon.h
 * A szabályos sokszöget megvalósító osztály fájlja.
 */
#ifndef SHAPE_POLYGON_H
#define SHAPE_POLYGON_H
#include "memtrace.h"

#include <iostream>
#include "vectormath.h"
#include "shape.h"

/**
 * A szabályos sokszöget megvalósító osztály.
 */
class /*Regular*/Polygon: public Shape {
    Vector center;
    Vector vertex;
    unsigned vertex_count;
    Segment closest_edge_to(Vector p) const;
    
public:
    
    /// Majdnem default konstruktor csak az adatfolyamból beolvasás céljára, amúgy memóriaszeméttel inicializál.
    /// @param vc vertex count, négyszög esetén 4 pl, >=3-má lesz téve
    Polygon(unsigned vc): vertex_count(vc > 3 ? vc : 3) { }
    
    /// @param vc vertex count, négyszög esetén 4 pl, >=3-má lesz téve
    Polygon(Vector center, Vector vertex, unsigned vc):
        center(center), vertex(vertex), vertex_count(vc > 3 ? vc : 3) { }
    
    bool has_point(Vector p) const;
    bool intersects_with(const Circle& c) const;
    
    void read_from(std::istream& is) {
        is >> center >> vertex;
    }
    void print_to(std::ostream& os) const {
        os << vertex_count << "-gon(center = " << center << ", vertex = " << vertex << ")";
    }
};

#endif // SHAPE_POLYGON_H
