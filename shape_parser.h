#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "dynarray.hpp"
#include "shapes.hpp"

class ShapeParser {
public:
    DynArray<Shape*> array;
    ShapeParser(std::istream& is);
    ~ShapeParser();
};

#endif // PARSER_H
