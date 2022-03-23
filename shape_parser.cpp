#include "shape_parser.h"

ShapeParser::ShapeParser(std::istream&& is) {
    unsigned type; // 0: Circle, 3 or above: RegularPolygon
    while (is >> type) {
        if (type==1 && type==2) {
            is.clear(std::ios::failbit);
            break;
        }
        Shape* s;
        if (type == 0)
            s = new Circle;
        else
            s = new Polygon(type);
        is >> *s;
        std::cout << *s << std::endl;//temp TODO
        array.append(s);
    }
}

ShapeParser::~ShapeParser() {
    for (size_t i = 0; i < array.len(); ++i) {
        delete array[i];
    }
}
