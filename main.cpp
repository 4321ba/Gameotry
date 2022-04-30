#include <iostream>
using std::ostream;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::flush;
// TODO cerr használata?
// TODO and or not helyett && || !
// is és os in és out helyett (iostream)
// TODO console.cpp-ben külön opcióként szétválasztani az utf8 és cpmittoménmi kódolást, hogy windowson is lehessen tesztelni utf8-cal (tesztprogram tesztelhessen utf8 kódokkal)
// TODO átnevezni .hpp-ről .h -ra a headeröket
//TODO Console fallback implementáció standard c++-szal / vagy olyan fordítási opció ahol nincs szükség rá (makrómágia)
//TODO memtrace!
#include <ctime>
#include <cstdlib> // for random

#include <fstream>

#include "vectormath.hpp"
#include "shapes.hpp"
#include "console.h"
#include "shape_parser.h"

#include "game_flappy_bird.h"
#include "game_snake.h"
#include "game_asteroids.h"


//#define GAME_MAIN // kikommentelendő? TODO: külön fájlba + 3. fájl a teszt
#define RUN_TEST

#ifdef GAME_MAIN
const double SECONDS_PER_GAME = 20.0;
int main() {
    srand(time(NULL));
    Console& con = Console::con();
    con.clrscr();
    
    int width = 80, height = 25;
    con.getsize(width, height);
    Screen screen(width, 2 * (height - 1/*for displaying fps count*/));
//     GameFlappyBird game;
//    std::ifstream snl("snake_level.txt");
//   GameSnake game(snl);
//    if (!snl.eof())
//        return 1;
     GameAsteroids game;
    bool success = game.play(con, screen, SECONDS_PER_GAME);
    cout << (success ? "Success!" : "Failure...") << endl;
}

#else
#ifndef RUN_TEST
bool outside_of_unit_circle(const Shape& s) {
    return !s.intersects_with(Circle(Vector(0, 0), 1.0));
}

int main() {
    const char* filename = "snake_level.txt";
    std::ifstream is(filename);
    ShapeParser p(is, outside_of_unit_circle);
    if (!is.eof()) {
        cerr << "Invalid input format in file " << filename << endl;
        return 1;
    }
    
    for (const Shape& s: p)
        cout << s << endl;
}
#else
//#define MEMTRACE
//#include "memtrace.h"
#include "gtest_lite.h"
#include <sstream>

int main() {

    TEST(Vector, constructor) {
        Vector v(1.4,2.7);
        EXPECT_DOUBLE_EQ(1.4, v.x) << "Vector ctor x" << endl;
        EXPECT_DOUBLE_EQ(2.7, v.y) << "Vector ctor y" << endl;
        v = Vector(0.0,-99992.3);
        EXPECT_DOUBLE_EQ(0.0, v.x) << "Vector ctor x" << endl;
        EXPECT_DOUBLE_EQ(-99992.3, v.y) << "Vector ctor y" << endl;
        v = Vector::polar(5.0,0.643501108793284); // =36.86°, tg=3/4
        EXPECT_DOUBLE_EQ(4.0, v.x) << "Vector polar ctor x" << endl;
        EXPECT_DOUBLE_EQ(3.0, v.y) << "Vector polar ctor y" << endl;
    } ENDM

    TEST(Vector, constant) {
        EXPECT_DOUBLE_EQ(0.0, Vector::UP.x) << "UP x" << endl;
        EXPECT_DOUBLE_EQ(-1.0, Vector::UP.y) << "UP y" << endl;
    } ENDM

    TEST(Vector, operators) {
        Vector v1(1.4,2.7);
        Vector v2(-6.3,14.0);
        Vector add = v1 + v2;
        EXPECT_DOUBLE_EQ(-4.9, add.x) << "Vector add x" << endl;
        EXPECT_DOUBLE_EQ(16.7, add.y) << "Vector add y" << endl;
        Vector addeq = v1;
        EXPECT_DOUBLE_EQ(1.4, addeq.x) << "Vector copyctor x" << endl;
        EXPECT_DOUBLE_EQ(2.7, addeq.y) << "Vector copyctor y" << endl;
        addeq += v2;
        EXPECT_DOUBLE_EQ(-4.9, addeq.x) << "Vector addeq x" << endl;
        EXPECT_DOUBLE_EQ(16.7, addeq.y) << "Vector addeq y" << endl;
        Vector sub = v1 - v2;
        EXPECT_DOUBLE_EQ(7.7, sub.x) << "Vector sub x" << endl;
        EXPECT_DOUBLE_EQ(-11.3, sub.y) << "Vector sub y" << endl;
        Vector stretch = v1 * 3.5;
        EXPECT_DOUBLE_EQ(4.9, stretch.x) << "Vector stretch x" << endl;
        EXPECT_DOUBLE_EQ(9.45, stretch.y) << "Vector stretch y" << endl;
        double dot = v1 * v2;
        EXPECT_DOUBLE_EQ(28.98, dot) << "Vector dot product" << endl;
    } ENDM

    TEST(Vector, calculations) {
        Vector v1(1.4,2.7);
        Vector v2(-6.3,14.0);
        double dist = v1.distance_to(v2);
        EXPECT_DOUBLE_EQ(13.674063039199432, dist) << "Vector distance" << endl;
        double dist_squared = v1.distance_squared_to(v2);
        EXPECT_DOUBLE_EQ(186.98, dist_squared) << "Vector distance squared" << endl;
        double angle = v2.angle_to(v1);
        EXPECT_DOUBLE_EQ(-0.972652083130931, angle) << "Vector angle" << endl;
        Vector rot = v1;
        rot.rotate(MATH_PI / 2);
        EXPECT_DOUBLE_EQ(-2.7, rot.x) << "Vector rotate1 x" << endl;
        EXPECT_DOUBLE_EQ(1.4, rot.y) << "Vector rotate1 y" << endl;
        rot.rotate(1.0);
        EXPECT_DOUBLE_EQ(-2.636875604575032, rot.x) << "Vector rotate2 x" << endl;
        EXPECT_DOUBLE_EQ(-1.515548430765925, rot.y) << "Vector rotate2 y" << endl;
        rot = v1;
        rot.rotate_around(v2, MATH_PI);
        EXPECT_DOUBLE_EQ(-14.0, rot.x) << "Vector rotate around v2 x" << endl;
        EXPECT_DOUBLE_EQ(25.3, rot.y) << "Vector rotate around v2 y" << endl;
    } ENDM
    
    TEST(Vector, streamoperators) {
        Vector v(1.4,2.7);
        std::stringstream ss1;
        ss1 << v;
        EXPECT_STREQ("Vector(1.4, 2.7)", ss1.str().c_str());
        std::stringstream ss2("-6.3 14");
        ss2 >> v;
        EXPECT_DOUBLE_EQ(-6.3, v.x);
        EXPECT_DOUBLE_EQ(14.0, v.y);
    } ENDM
    
    TEST(Segment, calculations) {
        Vector v1(1.4,2.7);
        Vector v2(-6.3,14.0);
        EXPECT_THROW(Segment(v1, v1), std::logic_error&);
        Segment s(v1,v2);
        EXPECT_TRUE(s.is_point_to_the_left(v1 + Vector::LEFT));
        EXPECT_TRUE(s.is_point_to_the_left(v2 + Vector::LEFT));
        EXPECT_FALSE(s.is_point_to_the_left(v1 + Vector(0,1)));
        EXPECT_TRUE(s.is_point_to_the_left(Vector(0, 0)));
        Vector close = s.closest_point_to(Vector(100, 0));
        EXPECT_DOUBLE_EQ(1.4, close.x);
        EXPECT_DOUBLE_EQ(2.7, close.y);
        close = s.closest_point_to(Vector(3.2, 12.2));
        EXPECT_DOUBLE_EQ(-2.45, close.x);
        EXPECT_DOUBLE_EQ(8.35, close.y);
        std::stringstream ss;
        ss << s;
        EXPECT_STREQ("Segment(Vector(1.4, 2.7), Vector(-6.3, 14))", ss.str().c_str());
    } ENDM
    
}


#endif
#endif
