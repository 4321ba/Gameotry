#include "screen.h"
#include "console.h"

// modifying this will break the games, that have hardcoded values
const Vector Screen::size = Vector(80.0, 50.0);

bool& Screen::idx(unsigned x, unsigned y) {
    if (x >= width or y >= height)
        throw std::range_error("Screen coordinate out of range");
    return data[y * width + x];
}

bool Screen::idx(unsigned x, unsigned y) const {
    if (x >= width or y >= height)
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
        start_y = (height - width * size.y / size.x) / 2.0;
        max_height -= start_y;
    // if the actual size is wider than the simulated
    } else {
        //std::cout << "wtf";
        start_x = (width - height * size.x / size.y) / 2.0;
        max_width -= start_x;
    }
    //std::cout<<size << " "<<width << " "<<height << " "<< start_x << " "<<start_y << " "<<max_width << " "<<max_height << " "<<std::endl;
    //char c;
    //std::cin >> c;
    for (unsigned x = start_x; x < max_width; ++x) {
        for (unsigned y = start_y; y < max_height; ++y) {
            double x_coord = (x - start_x) * size.x / (width - 2*start_x);
            double y_coord = (y - start_y) * size.y / (height - 2*start_y);
            //std::cout <<x << " "<<y  << " "<< Vector(x_coord, y_coord) << " " << s.has_point(Vector(x_coord, y_coord)) << std::endl;
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
