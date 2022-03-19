#ifndef SHAPES_H
#define SHAPES_H

#include "vectormath.hpp"

class Circle;

class Shape {
public:
    virtual bool has_point(Vector p) const = 0;
    virtual bool intersects_with(const Circle& c) const = 0;
};

class Circle: public Shape {
    Vector center;//TODO const?
    double radius;
public:
    Circle(Vector center, Vector arc_point):
        center(center), radius(center.distance_to(arc_point)) { }
    
    Vector get_center() const { return center; }
    //double get_radius() const { return radius; }
    
    bool has_point(Vector p) const {
        return radius >= center.distance_to(p);
    }
    bool intersects_with(const Circle& c) const {
        return c.radius + radius >= c.center.distance_to(center);
    }
};

class /*Regular*/Polygon: public Shape {
    Vector center;
    Vector vertex;//TODO const itt is?
    int vertex_count;
    Segment closest_edge_to(Vector p) const;
    
public:
    Polygon(Vector center, Vector vertex, int vertex_count): // TODO vertex_count>=3??
        center(center), vertex(vertex), vertex_count(vertex_count) { }
    
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
};

#endif // SHAPES_H
