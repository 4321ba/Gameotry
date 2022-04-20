#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "dynarray.hpp"
#include "shapes.hpp"

class ShapeParser {
    DynArray<Shape*> array;
    typedef DynArray<Shape*>::Iterator SuperIt;
    
    ShapeParser(const ShapeParser&);
    ShapeParser& operator=(const ShapeParser&);
public:
    // pred-del meg lehet mondani, hogy eltároljuk-e az adott alakzatot
    ShapeParser(std::istream& is,
                bool (*pred)(const Shape&) = [](const Shape&) { return true; }
               );
    ~ShapeParser();
    
    // because we want to return Shape& and not Shape*& when dereferencing the iterator
    class Iterator: public SuperIt {
    public:
        Iterator(const SuperIt& it): SuperIt(it) { }
        const Shape& operator*() { return *SuperIt::operator*(); }
    };
    
    Iterator begin() { return array.begin(); }
    Iterator end() { return array.end(); }
};

#endif // PARSER_H
