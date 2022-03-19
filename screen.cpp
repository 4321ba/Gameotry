#include "screen.h"
#include "console.h"

// modifying this will break the games, that have hardcoded values TODO? nem kell instance-t adni használathoz! statikus adattag!
const Vector Screen::size = Vector(80.0, 50.0);

bool& Screen::idx(unsigned x, unsigned y) {
    if (x >= width || y >= height)
        throw std::range_error("Screen coordinate out of range");
    return data[y * width + x];
}

bool Screen::idx(unsigned x, unsigned y) const {
    if (x >= width || y >= height)
        throw std::range_error("Screen coordinate out of range");
    return data[y * width + x];
}

void Screen::clear() {
    for (unsigned x = 0; x < width; ++x)
        for (unsigned y = 0; y < height; ++y)
            idx(x, y) = false;
}

Screen::Screen(unsigned w, unsigned h): width(w), height(h - h % 2) {
    data = new bool[width * height];
    clear();
}

void Screen::draw_vector(const Vector& v) {// TODO remove
    unsigned x_coord = v.x / size.x * width;
    unsigned y_coord = v.y / size.y * height;
    idx(x_coord, y_coord) = true;
}

void Screen::draw_shape(const Shape& s) {
    unsigned start_x = 0, start_y = 0, max_width = width, max_height = height;
    // if the simulated ratio is wider than the actual
    if (size.x / size.y > (double)width / height) {
        // we need to add black bars at the top and bottom
        start_y = (height - width * size.y / size.x) / 2.0;
        max_height -= start_y;
    // if the actual size is wider than the simulated
    } else {
        // we need to add black bars at the left and right
        start_x = (width - height * size.x / size.y) / 2.0;
        max_width -= start_x;
    }
    for (unsigned x = start_x; x < max_width; ++x) {
        double x_coord = size.x * (x - start_x) / (max_width - start_x);
        for (unsigned y = start_y; y < max_height; ++y) {
            double y_coord = size.y * (y - start_y) / (max_height - start_y);
            if (s.has_point(Vector(x_coord, y_coord)))
                idx(x, y) = true;
        }
    }
}

void Screen::render(std::ostream& out) const {
    for (unsigned y = 0; y < height / 2; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            bool up = idx(x, 2 * y);
            bool down = idx(x, 2 * y + 1);
            out << Console::getblock((Console::Block)(2 * up + down));
        }
        out << '\n';
    }
    out.flush();
}
