#include <iostream>
using std::ostream;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include "vectormath.hpp"
#include "shapes.hpp"
#include "console.h"

class Screen {
    static const int height = 80, width = 120; // height legyen 2-vel osztható!
    bool data[width][height];
public:
    Screen() {
        for (int x = 0; x < width; ++x)
            for (int y = 0; y < height; ++y)
                data[x][y] = false;
    }
    
    void draw_vector(const Vector& v) {
        //cout << v<<endl;
        int x_coord = v.x + 0.5;
        int y_coord = v.y + 0.5;
        if (x_coord < 0 or x_coord >= width or y_coord < 0 or y_coord >= height)
            throw std::range_error("Vector is not on screen!");//TODO vhogy máshogy (?)
        data[x_coord][y_coord] = true;
    }
    
    void draw_shape(const Shape& s) {
        for (int x = 0; x < width; ++x)
            for (int y = 0; y < height; ++y)
                if (s.has_point(Vector(x, y)))
                    data[x][y] = true;
    }
    
    void render(ostream& out) const {
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
};

ostream& operator << (ostream& out, const Screen& s) {
    s.render(out);
    return out;
}


// https://www.cplusplus.com/reference/thread/this_thread/sleep_for/
// https://stackoverflow.com/questions/41077377/how-to-get-current-time-in-milliseconds
// http://www.cplusplus.com/reference/chrono/
#include <thread>
#include <chrono>
using std::this_thread::sleep_for;
using std::chrono::nanoseconds;
using clk = std::chrono::high_resolution_clock;
#include <cstdlib>//for random

int main() {
    srand (time(NULL));

    Console& con = Console::con();
    con.clrscr();
    
    
    int y_offset = rand() % 40;
    double spike_x = -100;
    Vector bird_pos = Vector(20, 0);
    Vector bird_velocity = Vector(0, 0);
    const Vector gravity(0, 0.01);
    clk::time_point previously = clk::now();
    while(true) {
        Screen screen;
        char c = 0;
        if (con.kbhit()) {
            c = con.getch();
            bird_velocity = Vector(0, -0.6);
        }
        
        bird_velocity = bird_velocity + gravity;
        bird_pos = bird_pos + bird_velocity;
        Circle bird(bird_pos, bird_pos + Vector(3, 1));
        screen.draw_shape(bird);
        
        spike_x -= 0.6;
        if (spike_x < -30) {
            spike_x = 150;
            y_offset = rand() % 40;
        }
        Polygon spike1(Vector(spike_x, 0), Vector(spike_x, 10 + y_offset), 3);
        screen.draw_shape(spike1);
        Polygon spike2(Vector(spike_x, 80), Vector(spike_x, 30 + y_offset), 3);
        screen.draw_shape(spike2);
        if (spike1.intersects_with(bird) or spike2.intersects_with(bird))
            return 0;
        
        con.gotoxy(0, 0);
        cout << screen;
        
        
        clk::time_point now = clk::now();
        nanoseconds delta = now - previously;
        previously = now;
        cout << "mspt: " << 1000000.0/delta.count() << " " << c << endl;
        
        
        constexpr long int fps = 60;
        constexpr long int max_nspt = 1000000000 / fps;
        nanoseconds wait = nanoseconds(max_nspt) - delta;
        if (wait.count() > 0)
            sleep_for(wait);
        
    }
}

