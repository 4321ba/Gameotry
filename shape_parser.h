#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "dynarray.hpp"
#include "shapes.hpp"

class ShapeParser {
public:
    DynArray<Shape*> array;
    ShapeParser(std::istream&& is); //TODO inkább &, és a game_snake kapjon egy ilyenre referenciát a konstruktorában (?)
    ~ShapeParser();
    // TODO indexelés operátor, ami referenciát ad, hogy ne lehessen babrálni az array-val és a dinamikus tagokkal
};

#endif // PARSER_H
