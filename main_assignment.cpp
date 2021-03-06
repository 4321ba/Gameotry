/**
 * \file main_assignment.cpp
 * A feladat által kért főprogram megvalósítása.
 */
#include "memtrace.h"

#include <iostream>
#include <fstream>
#include <exception>
#include <limits>

#include "vectormath.h"
#include "shapes.h"
#include "shape_parser.h"

namespace {
    bool outside_of_unit_circle(const Shape& s) {
        return !s.intersects_with(Circle(Vector(0, 0), 1.0));
    }
}

/**
 * A feladat által kért főprogram megvalósítása.
 * 
 * A bemenetről koordinátapárokat vesz be, és a kimenetre kiírja, hogy a beolvasott fájlból mely alakzatok tartalmazzák azt a pontot.
 * A beolvasáskor eldobja az egységkörrel érintkező alakzatokat.
 * Paramétereket a könnyebb tesztelhetőség miatt kap.
 */
void main_assignment(std::istream& is, std::ostream& os) {
    std::ifstream file("snake_level.txt");
    ShapeParser parser(file, outside_of_unit_circle);
    if (!file.eof()) throw std::runtime_error("Missing file, or invalid input format in snake_level.txt!");
    
    os << "Please give coordinates in the following form: \"x y\" (without quotes), or type something else to quit:" << std::endl;
    Vector v;
    while (is >> v) {
        bool found_shape = false;
        for (const Shape& s: parser) {
            if (s.has_point(v)) {
                os << s << " has point " << v << "." << std::endl;
                found_shape = true;
            }
        }
        if (!found_shape)
            os << "No shapes were found that have point " << v << "." << std::endl;
    }
    if (is.eof())
        throw std::runtime_error("EOF found on standard input, exiting.");
    is.clear();
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
