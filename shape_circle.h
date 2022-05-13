/**
 * \file shape_circle.h
 * A kör alakzatot megvalósító osztály fájlja.
 */
#ifndef SHAPE_CIRCLE_H
#define SHAPE_CIRCLE_H
#include "memtrace.h"

#include <iostream>
#include "vectormath.h"
#include "shape.h"

class Circle: public Shape {
    Vector center;
    double radius;
public:
    Circle() { }
    Circle(Vector center, Vector arc_point):
        center(center), radius(center.distance_to(arc_point)) { }
    Circle(Vector center, double radius):
        center(center), radius(fabs(radius)) { }
    
    Vector get_center() const { return center; }
    
    bool has_point(Vector p) const {
        return radius >= center.distance_to(p);
    }
    bool intersects_with(const Circle& c) const {
        return c.radius + radius >= c.center.distance_to(center);
    }
    void read_from(std::istream& is) {
        Vector arc_point;
        is >> center >> arc_point;
        radius = center.distance_to(arc_point);
    }
    void print_to(std::ostream& os) const {
        os << "Circle(center = " << center << ", radius = " << radius << ")";
    }
};

#endif // SHAPE_CIRCLE_H
