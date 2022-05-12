#include <iostream>
#include <fstream>
#include <exception>

#include "vectormath.h"
#include "shapes.h"
#include "shape_parser.h"

bool outside_of_unit_circle(const Shape& s) {
    return !s.intersects_with(Circle(Vector(0, 0), 1.0));
}

void main_assignment() {
    std::ifstream is("snake_level.txt");
    ShapeParser parser(is, outside_of_unit_circle);
    if (!is.eof())
        throw std::runtime_error("Invalid input format in file snake_level.txt!");
    
    Vector v;
    while (std::cin >> v)
        for (const Shape& s: parser)
            if (s.has_point(v))
                std::cout << s << std::endl;
}
