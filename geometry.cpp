#include <cmath>

#include <iostream>
using std::ostream;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
/*
#include <algorithm>
using std::max;*/

constexpr double MATH_PI = 3.14159265358979323846;

struct Vector {
    double x, y;
    Vector(double x, double y): x(x), y(y) { }
    //Vector(Vector const &v): x(v.x), y(v.y) { }
    Vector operator + (Vector other) const {
        return Vector(x + other.x, y + other.y);
    }
    Vector operator - (Vector other) const {
        return Vector(x - other.x, y - other.y);
    }
    Vector operator * (double other) const { // skalárral nyújtás
        return Vector(x * other, y * other);
    }
    double operator * (Vector other) const { // skalárszorzat
        return x * other.x + y * other.y;
    }
    double distance_to(Vector v) const {
        return sqrt(distance_squared_to(v));
    }
    double distance_squared_to(Vector v) const {
        double x_dist = x - v.x;
        double y_dist = y - v.y;
        return x_dist * x_dist + y_dist * y_dist;
    }
    double angle_to(Vector v) const {
        return atan2(y - v.y, x - v.x);
    }
    void rotate(double angle) {
        double temp = x;
        x = temp * cos(angle) - y * sin(angle);
        y = temp * sin(angle) + y * cos(angle);
    }
    void rotate_around(Vector c, double angle) {
        Vector diff = *this - c;
        diff.rotate(angle);
        *this = c + diff;
    }
};

ostream& operator << (ostream& out, const Vector& v) {
    out << "Vector(" << v.x << ", " << v.y << ")";
    return out;
}

// represents a segment, as well as a line
struct Segment {
    Vector a, b; // két végpont
    Segment(Vector a, Vector b): a(a), b(b) { }
    bool is_point_to_the_left(Vector p) const {
        // m = (b.y-a.y)/(b.x-a.x)
        // y - y0 = m * (x - x0)
        // (p.y - a.y)*(b.x-a.x) = (p.x - a.x)*(b.y-a.y)
        // https://stackoverflow.com/questions/1560492/how-to-tell-whether-a-point-is-to-the-right-or-left-side-of-a-line
        // ((b.X - a.X)*(c.Y - a.Y) - (b.Y - a.Y)*(c.X - a.X)) > 0;
        //return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x) > 0;
        Vector ab = b - a;
        Vector ap = p - a;
        return ab.x * ap.y - ab.y * ap.x > 0;
    }
    Vector closest_point_to(Vector p) const { // result is between a and b
        // https://stackoverflow.com/questions/3120357/get-closest-point-to-a-line
        Vector ab = b - a;
        Vector ap = p - a;
        double dot = ab * ap;
        double lerp_weight = dot / a.distance_squared_to(b);
        if (lerp_weight < 0)
            return a;
        if (lerp_weight > 1)
            return b;
        return a + ab * lerp_weight;
    }
};

ostream& operator << (ostream& out, const Segment& s) {
    out << "Segment(" << s.a << ", " << s.b << ")";
    return out;
}


class Circle;
class Shape {
public:
    virtual bool has_point(Vector p) const = 0;//??
    virtual bool intersects_with(const Circle& c) const = 0;
};

class Circle: public Shape {
    Vector center;
    double radius;
public:
    Circle(Vector center, Vector arc_point): center(center) {
        radius = center.distance_to(arc_point);
    }
    
    Vector get_center() const { return center; }
    double get_radius() const { return radius; }
    
    bool has_point(Vector p) const {
        return radius >= center.distance_to(p);
    }
    bool intersects_with(const Circle& c) const {
        return c.get_radius() + radius >= c.get_center().distance_to(center);
    }
};

class /*Regular*/Polygon: public Shape {
    Vector center;
    Vector vertex;
    int vertex_count;
    Segment closest_edge_to(Vector p) const { // returns in positive direction: seg.b is "more" in the positive dir then a
        double angle_to_vertex = center.angle_to(vertex);
        double angle_to_point = center.angle_to(p);
        double one_edge_angle = 2 * MATH_PI / vertex_count;
        while (angle_to_point < angle_to_vertex)
            angle_to_point += 2 * MATH_PI;
        double angle_difference = angle_to_point - angle_to_vertex;
        Vector prev_vertex = vertex;
        double prev_vertex_angle_diff = (int)(angle_difference / one_edge_angle) * one_edge_angle;
        prev_vertex.rotate_around(center, prev_vertex_angle_diff);
        Vector next_vertex = prev_vertex;
        next_vertex.rotate_around(center, one_edge_angle);
        return Segment(prev_vertex, next_vertex);
    }
    
public:
    Polygon(Vector center, Vector vertex, int vertex_count):
        center(center), vertex(vertex), vertex_count(vertex_count) { }
    
    
    bool has_point(Vector p) const {
        return closest_edge_to(p).is_point_to_the_left(p);
    }
    
    bool intersects_with(const Circle& c) const {
        Vector center = c.get_center();
        if (has_point(center))
            return true;
        Segment closest_edge = closest_edge_to(center);
        return c.has_point(closest_edge.closest_point_to(center));
    }
};


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
            throw std::range_error("Vector is not on screen!");
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
                const char *boxes[] = {" ", "▄", "▀", "█"};
                out << boxes[2 * up + down];
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
//#include <cstdio>
#include <unistd.h>//https://stackoverflow.com/questions/21197977/how-can-i-prevent-scanf-to-wait-forever-for-an-input-character
#include <poll.h>
#include <cstdlib>//for random

int main() {
    srand (time(NULL));
    int y_offset = rand() % 40;
    double spike_x = -100;
    Vector bird_pos = Vector(20, 0);
    Vector bird_velocity = Vector(0, 0);
    const Vector gravity(0, 0.01);
    clk::time_point previously = clk::now();
    while(true) {
        Screen screen;
        
        struct pollfd mypoll = { STDIN_FILENO, POLLIN|POLLPRI, 0 };
        char c;
        if( poll(&mypoll, 1, 0) ) {
            scanf("%c", &c);
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
        
        cout << "\x1B[H";//https://www2.ccs.neu.edu/research/gpc/VonaUtils/vona/terminal/vtansi.htm
        cout << screen;
        
        
        clk::time_point now = clk::now();
        nanoseconds delta = now - previously;
        previously = now;
        cout << "mspt: " << 1000000.0/delta.count() << endl;
        
        constexpr long int fps = 60;
        constexpr long int max_nspt = 1000000000 / fps;
        nanoseconds wait = nanoseconds(max_nspt) - delta;
        if (wait.count() > 0)
            sleep_for(wait);
        
    }
}


/*
 
        Screen screen;
        Circle circ(Vector(45, 40), Vector(42, 41));
        screen.draw_shape(circ);
        
        cpos.y += 1;
        epos.y += 1;
        epos.rotate_around(cpos, 0.1);
        Polygon trig(cpos, epos, 4);
        screen.draw_shape(trig);
        
        if (trig.intersects_with(circ)) {
            cpos = cpos + Vector(1, -30);
            epos = epos + Vector(1, -30);
        }
        
        cout << "\x1B[H";//https://www2.ccs.neu.edu/research/gpc/VonaUtils/vona/terminal/vtansi.htm
        cout << screen;
        
 */

/*
 int main() {
    Vector v = Vector(11, 16);
    while(true) {
        Screen screen;
        Circle circ(Vector(10, 10), Vector(11, 15));
        screen.draw_shape(circ);
        
        v.rotate_around(Vector(23, 20), 0.03);
        Polygon trig(Vector(23, 20), v, 3);
        screen.draw_shape(trig);
        
        Polygon square(Vector(50, 45), v, 4);
        screen.draw_shape(square);
        
        Vector center(60, 10);
        screen.draw_vector(center);
        Vector p(68, 11);
        for (int i = 0; i < 5; ++i) {
            screen.draw_vector(p);
            p.rotate_around(center, 2 * MATH_PI / 5);
        }
        cout << "\x1B[H";//https://www2.ccs.neu.edu/research/gpc/VonaUtils/vona/terminal/vtansi.htm
        cout << screen;
        
    }
}
 */
