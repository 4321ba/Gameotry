/**
 * \file vector.h
 * Két dimenziós, lebegőpontos (double) vektor (= irányított szakasz) megvalósítása.
 */
#ifndef VECTOR_H
#define VECTOR_H
#include "memtrace.h"

#include <cmath>
#include <iostream>

/**
 * Két dimenziós, lebegőpontos (double) vektor (= irányított szakasz) megvalósítása.
 */
struct Vector {
    double x, y;
    
    static const Vector UP, DOWN, LEFT, RIGHT;
    
    /// Default konstruktor, csak streamből beolvasás céljára. Memóriaszeméttel inicializál.
    Vector() { } // ne legyen felesleges =0 értékadás!, mint ahogy `int x;` -nél sincs
    
    /// Descartes-koordinátás konstruktor.
    Vector(double x, double y): x(x), y(y) { }
    
    /// Polárkoordinátás konstruktor-szerűség.
    static Vector polar(double r, double angle) { return Vector(r * cos(angle), r * sin(angle)); }

    Vector operator+(Vector other) const {
        return Vector(x + other.x, y + other.y);
    }
    Vector& operator+=(Vector other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vector operator-(Vector other) const {
        return Vector(x - other.x, y - other.y);
    }
    Vector operator*(double other) const { // stretch
        return Vector(x * other, y * other);
    }
    double operator*(Vector other) const { // dot product
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
    /// radiánt ad, jobbra van a 0, a pozitív irány a +x tengelytől a +y tengely irányába mutat
    double angle_to(Vector v) const {
        return atan2(v.y - y, v.x - x);
    }
    /// @param angle radián, jobbra van a 0, a pozitív irány a +x tengelytől a +y tengely irányába mutat
    void rotate(double angle) { // radian ofc, (right=0,) clockwise=positive
        double temp = x;
        x = temp * cos(angle) - y * sin(angle);
        y = temp * sin(angle) + y * cos(angle);
    }
    /// @param c a forgatás középpontja
    /// @param angle radián, jobbra van a 0, a pozitív irány a +x tengelytől a +y tengely irányába mutat
    void rotate_around(Vector c, double angle) {
        Vector diff = *this - c;
        diff.rotate(angle);
        *this = c + diff;
    }
};

inline std::istream& operator>>(std::istream& in, Vector& v) {
    return in >> v.x >> v.y;
}

inline std::ostream& operator<<(std::ostream& out, const Vector& v) {
    return out << "Vector(" << v.x << ", " << v.y << ")";
}

#endif // VECTOR_H
