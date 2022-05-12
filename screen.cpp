#include "screen.h"
#include "console.h"

// modifying this will break the games, that have hardcoded values TODO? nem kell instance-t adni használathoz! statikus adattag!
const Vector Screen::size = Vector(80.0, 50.0);

bool& Screen::idx(unsigned x, unsigned y) {
    if (x >= width || y >= height)
        throw std::out_of_range("Screen coordinate out of range");
    return data[y * width + x];
}

bool Screen::idx(unsigned x, unsigned y) const {
    if (x >= width || y >= height)
        throw std::out_of_range("Screen coordinate out of range");
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

void Screen::draw_shape(const Shape& shape) {
    unsigned start_x = 0, start_y = 0, max_width = width, max_height = height;
    // if the simulated ratio is wider than the actual
    // ha a szimulált képarány szélesebb, mint az igazi
    if (size.x / size.y > (double)width / height) {
        // we need to add black bars at the top and bottom
        // ekkor a fekete csíkokat alulra és felülre kell tenni
        start_y = (height - width * size.y / size.x) / 2.0;
        max_height -= start_y;
    // if the actual size is wider than the simulated
    // ha az igazi képméret szélesebb, mint a szimulált
    } else {
        // we need to add black bars at the left and right
        // ekkor a fekete csíkokat jobbra és balra kell tenni
        start_x = (width - height * size.x / size.y) / 2.0;
        max_width -= start_x;
    }
    // végigmegyünk azokon az igazi, képernyőn levő képpontokon, ahova tényleg rajzolni szeretnénk
    for (unsigned x = start_x; x < max_width; ++x) {
        // átfordítjuk a szimulált x koordinátára
        double x_coord = size.x * (0.5 /*for rounding*/ + x - start_x) / (max_width - start_x);
        for (unsigned y = start_y; y < max_height; ++y) {
            // és a szimulált y koordinátára
            double y_coord = size.y * (0.5 /*for rounding*/ + y - start_y) / (max_height - start_y);
            // ha a szimulált koordináta a megkapott alakzaton belül van,
            // akkor a valós! koordináta helyére beállítjuk a pixelt
            if (shape.has_point(Vector(x_coord, y_coord)))
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
