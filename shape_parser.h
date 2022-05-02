#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "dynarray.hpp"
#include "shapes.h"

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
    // NEM JÓK AZ ÖRÖKÖLT TYPEDEFJEI! vszeg furcsán fog viselkedni std::algoritmusokkal
    // mert ennek nincs is value_type-ja, Shape absztrakt
    class Iterator: public SuperIt {
    public:
        Iterator(const SuperIt& it): SuperIt(it) { }
        const Shape& operator*() { return *SuperIt::operator*(); }
    };
    
    Iterator begin() { return array.begin(); }
    Iterator end() { return array.end(); }
};

#endif // PARSER_H
