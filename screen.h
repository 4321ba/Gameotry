#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include "shapes.hpp"

class Screen {
    static const int height = 80, width = 120; // height legyen 2-vel osztható!
    bool data[width][height];
public:
    Screen();
    void draw_vector(const Vector& v);
    void draw_shape(const Shape& s);
    void render(std::ostream& out) const;
};

inline std::ostream& operator << (std::ostream& out, const Screen& s) {
    s.render(out);
    return out;
}

#endif // SCREEN_H
