#ifndef VECTORMATH_H
#define VECTORMATH_H

#include <cmath>

#include <iostream>
using std::ostream;

constexpr double MATH_PI = 3.14159265358979323846;

struct Vector {
    double x, y;//TODO priváttá ha nem kell igazából? meh, de lehet getterekkel megúszom
    
    static const Vector UP, DOWN, LEFT, RIGHT;
    
    Vector(double x, double y): x(x), y(y) { }

    Vector operator + (Vector other) const {
        return Vector(x + other.x, y + other.y);
    }
    Vector operator - (Vector other) const {
        return Vector(x - other.x, y - other.y);
    }
    Vector operator * (double other) const { // stretch
        return Vector(x * other, y * other);
    }
    double operator * (Vector other) const { // dot product
        return x * other.x + y * other.y;
    }
    double distance_to(Vector v) const {
        return sqrt(distance_squared_to(v));
    }
    double distance_squared_to(Vector v) const {
        double x_dist = x - v.x;
        double y_dist = y - v.y;
        return x_dist * x_dist + y_dist * y_dist;
    }
    double angle_to(Vector v) const {
        return atan2(y - v.y, x - v.x);
    }
    void rotate(double angle) {
        double temp = x;
        x = temp * cos(angle) - y * sin(angle);
        y = temp * sin(angle) + y * cos(angle);
    }
    void rotate_around(Vector c, double angle) {
        Vector diff = *this - c;
        diff.rotate(angle);
        *this = c + diff;
    }
};

inline ostream& operator << (ostream& out, const Vector& v) {
    out << "Vector(" << v.x << ", " << v.y << ")";
    return out;
}

// represents a segment, or a line
struct Segment {
    Vector a, b; // 2 endpoints
    Segment(Vector a, Vector b): a(a), b(b) { }
    bool is_point_to_the_left(Vector p) const;
    Vector closest_point_to(Vector p) const;
};

inline ostream& operator << (ostream& out, const Segment& s) {
    out << "Segment(" << s.a << ", " << s.b << ")";
    return out;
}

#endif // VECTORMATH_H
