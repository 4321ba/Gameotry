#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>
#include "vectormath.hpp"

class Circle;

class Shape {
public:
    virtual bool has_point(Vector p) const = 0;
    virtual bool intersects_with(const Circle& c) const = 0;
    
    // consumes 4 doubles if it can: center.x, center.y, vertex.x, vertex.y
    virtual void read_from(std::istream& is) = 0;
    virtual void print_to(std::ostream& os) = 0;
    virtual ~Shape() {}
};

inline std::istream& operator>>(std::istream& is, Shape& s) {
    s.read_from(is);
    return is;
}

inline std::ostream& operator<<(std::ostream& os, Shape& s) {
    s.print_to(os);
    return os;
}

class Circle: public Shape {
    Vector center;
    double radius;
public:
    Circle() { }
    Circle(Vector center, Vector arc_point):
        center(center), radius(center.distance_to(arc_point)) { }
    
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
    void print_to(std::ostream& os) {
        os << "Circle(center = " << center << ", radius = " << radius << ")";
    }
};

class /*Regular*/Polygon: public Shape {
    Vector center;
    Vector vertex;
    int vertex_count;
    Segment closest_edge_to(Vector p) const;
    
public:
    Polygon(int vc): vertex_count(vc > 3 ? vc : 3) { }
    Polygon(Vector center, Vector vertex, int vc):
        center(center), vertex(vertex), vertex_count(vc > 3 ? vc : 3) { }
    
    bool has_point(Vector p) const {
        return closest_edge_to(p).is_point_to_the_left(p);
    }
    
    bool intersects_with(const Circle& c) const {
        Vector center = c.get_center();
        if (has_point(center))
            return true;
        Segment closest_edge = closest_edge_to(center);
        return c.has_point(closest_edge.closest_point_to(center));
    }
    void read_from(std::istream& is) {
        is >> center >> vertex;
    }
    void print_to(std::ostream& os) {
        os << vertex_count <<"-gon(center = " << center << ", vertex = " << vertex << ")";
    }
};

#endif // SHAPES_H
