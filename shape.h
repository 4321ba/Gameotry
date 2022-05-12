#ifndef SHAPE_H
#define SHAPE_H
#include "memtrace.h"

#include <iostream>
#include "vectormath.h"

class Circle;

class Shape {
public:
    virtual bool has_point(Vector p) const = 0;
    virtual bool intersects_with(const Circle& c) const = 0;
    
    // consumes 4 doubles if it can: center.x, center.y, vertex.x, vertex.y
    virtual void read_from(std::istream& is) = 0;
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
