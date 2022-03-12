#include "screen.h"
#include "console.h"

Screen::Screen() {
    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
            data[x][y] = false;
}

void Screen::draw_vector(const Vector& v) {
    //cout << v<<endl;
    int x_coord = v.x + 0.5;
    int y_coord = v.y + 0.5;
    if (x_coord < 0 or x_coord >= width or y_coord < 0 or y_coord >= height)
        throw std::range_error("Vector is not on screen!");//TODO vhogy máshogy (?)
    data[x_coord][y_coord] = true;
}

void Screen::draw_shape(const Shape& s) {
    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
            if (s.has_point(Vector(x, y)))
                data[x][y] = true;
}

void Screen::render(std::ostream& out) const {
    for (int y = 0; y < height / 2; ++y) {
        for (int x = 0; x < width; ++x) {
            bool up = data[x][2 * y];
            bool down = data[x][2 * y + 1];
            out << Console::getblock((Console::Block)(2 * up + down));
        }
        out << '\n';
    }
    out.flush();
}
