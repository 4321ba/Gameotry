#ifndef VECTORMATH_H
#define VECTORMATH_H

#include <cmath>
#include <iostream>
#include <stdexcept>

constexpr double MATH_PI = 3.14159265358979323846;

struct Vector {
    double x, y;
    
    static const Vector UP, DOWN, LEFT, RIGHT;
    
    Vector() { } // ne legyen felesleges =0 értékadás!, mint ahogy `int x;` -nél sincs
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
    void rotate(double angle) { // radian ofc, (right=0,) clockwise=positive
        double temp = x;
        x = temp * cos(angle) - y * sin(angle);
        y = temp * sin(angle) + y * cos(angle);
    }
    void rotate_around(Vector c, double angle) {
        Vector diff = *this - c;
        diff.rotate(angle);
        *this = c + diff;
    }
    friend std::istream& operator>>(std::istream& in, Vector& v);
};

inline std::istream& operator>>(std::istream& in, Vector& v) {
    return in >> v.x >> v.y;
}

inline std::ostream& operator<<(std::ostream& out, const Vector& v) {
    return out << "Vector(" << v.x << ", " << v.y << ")";
}

// represents a segment, or a line
struct Segment {
    Vector a, b; // 2 endpoints
    Segment(Vector a, Vector b): a(a), b(b) {
        if (a.x == b.x && a.y == b.y)
            throw std::runtime_error("2 endpoints of a segment cannot be the same!");
    }
    bool is_point_to_the_left(Vector p) const;
    Vector closest_point_to(Vector p) const;
};

inline std::ostream& operator<<(std::ostream& out, const Segment& s) {
    return out << "Segment(" << s.a << ", " << s.b << ")";
}

#endif // VECTORMATH_H
