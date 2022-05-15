/**
 * \file shape_parser.cpp
 * Az alakzatok beolvasása és newzása, illetve törlése.
 */
#include "memtrace.h"

#include "shape_parser.h"

//#include "assert.h"

ShapeParser::ShapeParser(std::istream& is, bool (*pred)(const Shape&)) {
    unsigned type; // 0: Circle, 3 or above: RegularPolygon
    while (is >> type) {
        if (type==1 || type==2) {
            is.clear(std::ios::failbit);
            break;
        }
        Shape* s;
        if (type == 0)
            s = new Circle;
        else
            s = new Polygon(type);
        is >> *s;
        if (is && pred(*s))
            array.append(s);
        else
            delete s;
    }
}

ShapeParser::~ShapeParser() {
    // elméletileg az iterátor dobhat exceptiont, ez pedig a clang-tidynak nem tetszett, hogy a destruktor ezt továbbdobhatja
    // ugyanakkor a catch lényegében sosem fut le, az pedig dead code-nak minősülne a code coverage szempontjából
    //try {
        for (Shape* s: array)
            delete s;
    //} catch (...) {
    //    assert(false);
    //}
}
