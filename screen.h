#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include "shapes.h"

class Screen {
    const unsigned width, height;
    bool* data;
    
    bool& idx(unsigned x, unsigned y);
    bool idx(unsigned x, unsigned y) const;
    
    // we don't allow these
    Screen(const Screen&);
    Screen& operator=(const Screen&);
public:
    // this is what it looks like from the outside (so that it's resolution independent)
    static const Vector size;
    Screen(unsigned w/*idth*/, unsigned h/*eight*/); // height will be made divisible by 2
    ~Screen() { delete[] data; }
    void draw_shape(const Shape& s);
    void render(std::ostream& out) const;
    void clear();
};

inline std::ostream& operator<<(std::ostream& out, const Screen& s) {
    s.render(out);
    return out;
}

#endif // SCREEN_H
