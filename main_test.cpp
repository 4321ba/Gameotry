/**
 * \file main_test.cpp
 * A tesztprogram, főprogram.
 * 
 * Itt valósulnak meg a unittesztek, illetve a feladat főprogram tesztje is.
 */
#include "memtrace.h"

#include <fstream>
#include <sstream>
#include <algorithm>

#include "vectormath.h"
#include "shapes.h"
#include "dynarray.hpp"
#include "shape_parser.h"
#include "screen.h"
#include "mains.h"

#include "gtest_lite.h"

/// Itt valósulnak meg a unittesztek, illetve a feladat főprogram tesztje is.
void main_test() {

    TEST(Vector, constructor) {
        Vector v(1.4,2.7);
        EXPECT_DOUBLE_EQ(1.4, v.x);
        EXPECT_DOUBLE_EQ(2.7, v.y);
        v = Vector(0.0,-99992.3);
        EXPECT_DOUBLE_EQ(0.0, v.x);
        EXPECT_DOUBLE_EQ(-99992.3, v.y);
        v = Vector::polar(5.0,0.643501108793284); // =36.86°, tg=3/4
        EXPECT_DOUBLE_EQ(4.0, v.x);
        EXPECT_DOUBLE_EQ(3.0, v.y);
    } ENDM

    TEST(Vector, constant) {
        EXPECT_DOUBLE_EQ(0.0, Vector::UP.x);
        EXPECT_DOUBLE_EQ(-1.0, Vector::UP.y);
    } ENDM

    TEST(Vector, operators) {
        Vector v1(1.4,2.7);
        Vector v2(-6.3,14.0);
        Vector add = v1 + v2;
        EXPECT_DOUBLE_EQ(-4.9, add.x);
        EXPECT_DOUBLE_EQ(16.7, add.y);
        Vector addeq = v1;
        EXPECT_DOUBLE_EQ(1.4, addeq.x);
        EXPECT_DOUBLE_EQ(2.7, addeq.y);
        addeq += v2;
        EXPECT_DOUBLE_EQ(-4.9, addeq.x);
        EXPECT_DOUBLE_EQ(16.7, addeq.y);
        Vector sub = v1 - v2;
        EXPECT_DOUBLE_EQ(7.7, sub.x);
        EXPECT_DOUBLE_EQ(-11.3, sub.y);
        Vector stretch = v1 * 3.5;
        EXPECT_DOUBLE_EQ(4.9, stretch.x);
        EXPECT_DOUBLE_EQ(9.45, stretch.y);
        double dot = v1 * v2;
        EXPECT_DOUBLE_EQ(28.98, dot);
    } ENDM

    TEST(Vector, calculations) {
        Vector v1(1.4,2.7);
        Vector v2(-6.3,14.0);
        double dist = v1.distance_to(v2);
        EXPECT_DOUBLE_EQ(13.674063039199432, dist);
        double dist_squared = v1.distance_squared_to(v2);
        EXPECT_DOUBLE_EQ(186.98, dist_squared);
        double angle = v2.angle_to(v1);
        EXPECT_DOUBLE_EQ(-0.972652083130931, angle);
        Vector rot = v1;
        rot.rotate(MATH_PI / 2);
        EXPECT_DOUBLE_EQ(-2.7, rot.x);
        EXPECT_DOUBLE_EQ(1.4, rot.y);
        rot.rotate(1.0);
        EXPECT_DOUBLE_EQ(-2.636875604575032, rot.x);
        EXPECT_DOUBLE_EQ(-1.515548430765925, rot.y);
        rot = v1;
        rot.rotate_around(v2, MATH_PI);
        EXPECT_DOUBLE_EQ(-14.0, rot.x);
        EXPECT_DOUBLE_EQ(25.3, rot.y);
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
    
    TEST(Circle, calculations) {
        Circle c(Vector(23, 45), Vector(25, 45));
        EXPECT_DOUBLE_EQ(23.0, c.get_center().x);
        EXPECT_TRUE(c.has_point(Vector(23, 45)));
        EXPECT_TRUE(c.has_point(Vector(24, 45)));
        EXPECT_TRUE(c.has_point(Vector(24, 46)));
        EXPECT_FALSE(c.has_point(Vector(25, 46)));
        EXPECT_FALSE(c.has_point(Vector(0, 0)));
        Circle c2(Vector(25, 46), 1);
        EXPECT_TRUE(c.intersects_with(c2));
        Circle c3(Vector(26, 46), 1);
        EXPECT_FALSE(c.intersects_with(c3));
        Circle c4(Vector(200, -100), 500);
        EXPECT_TRUE(c.intersects_with(c4));
        std::stringstream ss1;
        ss1 << c;
        EXPECT_STREQ("Circle(center = Vector(23, 45), radius = 2)", ss1.str().c_str());
        std::stringstream ss2("69.4 -42.8 23423.23 45564.54");
        ss2 >> c;
        EXPECT_DOUBLE_EQ(69.4, c.get_center().x);
        EXPECT_DOUBLE_EQ(-42.8, c.get_center().y);
        std::stringstream ss3;
        ss3 << c;
        EXPECT_STREQ("Circle(center = Vector(69.4, -42.8), radius = 51239)", ss3.str().c_str());
    } ENDM
    
    TEST(Polygon, triangle) {
        Polygon p(Vector(23, 45), Vector(25, 45), 3);
        EXPECT_TRUE(p.has_point(Vector(23, 45)));
        EXPECT_TRUE(p.has_point(Vector(24, 45)));
        EXPECT_FALSE(p.has_point(Vector(24, 46)));
        EXPECT_FALSE(p.has_point(Vector(25, 46)));
        EXPECT_FALSE(p.has_point(Vector(0, 0)));
        Circle c2(Vector(25, 46), 1);
        EXPECT_TRUE(p.intersects_with(c2));
        Circle c3(Vector(26, 46), 1);
        EXPECT_FALSE(p.intersects_with(c3));
        Circle c4(Vector(200, -100), 500);
        EXPECT_TRUE(p.intersects_with(c4));
        Circle c5(Vector(30, 45.1), 5);
        EXPECT_FALSE(p.intersects_with(c5));
        Circle c6(Vector(23, 45.1), 0.01);
        EXPECT_TRUE(p.intersects_with(c6));
        std::stringstream ss1;
        ss1 << p;
        EXPECT_STREQ("3-gon(center = Vector(23, 45), vertex = Vector(25, 45))", ss1.str().c_str());
        std::stringstream ss2("69.4 -42.8 23423.23 45564.54");
        ss2 >> p;
        std::stringstream ss3;
        ss3 << p;
        EXPECT_STREQ("3-gon(center = Vector(69.4, -42.8), vertex = Vector(23423.2, 45564.5))", ss3.str().c_str());
    } ENDM
    
    TEST(Polygon, square) {
        Polygon p(Vector(23, 45), Vector(25, 45), 4);
        EXPECT_TRUE(p.has_point(Vector(23, 45)));
        EXPECT_TRUE(p.has_point(Vector(24, 45)));
        EXPECT_TRUE(p.has_point(Vector(23.9, 46)));
        EXPECT_FALSE(p.has_point(Vector(24.1, 46)));
        EXPECT_FALSE(p.has_point(Vector(25, 46)));
        EXPECT_FALSE(p.has_point(Vector(0, 0)));
        Circle c2(Vector(25, 46), 1);
        EXPECT_TRUE(p.intersects_with(c2));
        Circle c3(Vector(26, 46), 1);
        EXPECT_FALSE(p.intersects_with(c3));
        Circle c4(Vector(200, -100), 500);
        EXPECT_TRUE(p.intersects_with(c4));
        Circle c5(Vector(30, 45.1), 5);
        EXPECT_FALSE(p.intersects_with(c5));
        Circle c6(Vector(23, 45.1), 0.01);
        EXPECT_TRUE(p.intersects_with(c6));
        std::stringstream ss1;
        ss1 << p;
        EXPECT_STREQ("4-gon(center = Vector(23, 45), vertex = Vector(25, 45))", ss1.str().c_str());
        std::stringstream ss2("69.4 -42.8 23423.23 45564.54");
        ss2 >> p;
        std::stringstream ss3;
        ss3 << p;
        EXPECT_STREQ("4-gon(center = Vector(69.4, -42.8), vertex = Vector(23423.2, 45564.5))", ss3.str().c_str());
    } ENDM
    
    
    TEST(DynArray, integer) {
        DynArray<int> arr;
        arr.append(1);
        arr.append(2);
        DynArray<int>::Iterator it = arr.begin();
        EXPECT_EQ(1, *it);
        EXPECT_NO_THROW(++it);
        EXPECT_EQ(2, *it);
        EXPECT_NO_THROW(++it);
        EXPECT_FALSE(it != arr.end());
        EXPECT_TRUE(it != arr.begin());
        EXPECT_THROW(*it, std::out_of_range&);
        arr.append(3);
        arr.append(4);
        arr.append(5);
        int test1[] = { 1, 2, 3, 4, 5 };
        EXPECT_TRUE(std::equal(test1, test1 + 5, arr.begin()));
        arr.append(165);
        arr.append(166);
        arr.append(167);
        arr.append(168);
        arr.append(169);
        int test2[] = { 1, 2, 3, 4, 5, 165, 166, 167, 168, 164 };
        EXPECT_FALSE(std::equal(test2, test2 + 10, arr.begin()));
        int test3[] = { 1, 2, 3, 4, 5, 165, 166, 167, 168, 169 };
        EXPECT_TRUE(std::equal(test3, test3 + 10, arr.begin()));
    } ENDM
    
    TEST(DynArray, vector) {
        DynArray<Vector> arr;
        arr.append(Vector(1.56, 345.6));
        arr.append(Vector(1.4556, 34345.6));
        DynArray<Vector>::Iterator it = arr.begin();
        EXPECT_DOUBLE_EQ(1.56, (*it).x); // nyilacska operátor nincs felülírva :/ a tervnek megfelelően
        EXPECT_NO_THROW(++it);
        EXPECT_DOUBLE_EQ(1.4556, (*it).x);
        EXPECT_NO_THROW(++it);
        EXPECT_FALSE(it != arr.end());
        EXPECT_TRUE(it != arr.begin());
        EXPECT_THROW(*it, std::out_of_range&);
        arr.append(Vector(2341.56, 34234235.6));
        arr.append(Vector(234231.56, 342342345.6));
        arr.append(Vector(134.56, 334324545.6));
        Vector test1[] = {
            Vector(1.56, 345.6),
            Vector(1.4556, 34345.6),
            Vector(2341.56, 34234235.6),
            Vector(234231.56, 342342345.6),
            Vector(134.56, 334324545.6),
        };
        EXPECT_TRUE(std::equal(test1, test1 + 5, arr.begin(),
                               [](Vector a, Vector b){ return a.x==b.x && a.y==b.y; }
                              ));
    } ENDM
    
    
    TEST(ShapeParser, parsing) {
        std::stringstream ss1("123 234 3242 343 fhdgh");
        ShapeParser sp1(ss1);
        EXPECT_FALSE(ss1.eof());
        EXPECT_THROW(*sp1.begin(), std::out_of_range&); // egy adat se szabad legyen bent
        
        std::stringstream ss2("123 234 3242 343 3476 3634 6834 56");
        ShapeParser sp2(ss2);
        EXPECT_TRUE(ss2.eof());
        EXPECT_NO_THROW(*sp2.begin());
        EXPECT_THROW(*++sp2.begin(), std::out_of_range&); // 1 shape kell legyen bent
        std::stringstream checkss;
        checkss << *sp2.begin();
        EXPECT_STREQ("123-gon(center = Vector(234, 3242), vertex = Vector(343, 3476))", checkss.str().c_str());
        
        std::ifstream fs("snake_level.txt");
        ShapeParser sp3(fs);
        EXPECT_TRUE(fs.eof());
        const char* expected[] = {
            "4-gon(center = Vector(40, -39.5), vertex = Vector(0, 0.5))",
            "4-gon(center = Vector(40, 89.5), vertex = Vector(0, 49.5))",
            "4-gon(center = Vector(-24.5, 25), vertex = Vector(0.5, 0))",
            "4-gon(center = Vector(104.5, 25), vertex = Vector(79.5, 0))",
            "Circle(center = Vector(15.1, 20.85), radius = 2.05)",
            "3-gon(center = Vector(41, 10.5), vertex = Vector(46, 10.5))",
            "6-gon(center = Vector(65, 37), vertex = Vector(60.7, 32.7))",
        };
        int idx = 0;
        for (const Shape& s: sp3) { // iterátor tesztelése
            std::stringstream ss;
            ss << s;
            EXPECT_STREQ(expected[idx++], ss.str().c_str());
        }
        EXPECT_EQ(7, idx);
        
        // 2 mint típus, az érvénytelen
        std::stringstream ss4("123 234 3242 343 3476 2 6834 56 23 434 52 4234");
        ShapeParser sp4(ss4);
        EXPECT_FALSE(ss4.eof());
        EXPECT_FALSE((bool)ss4);
        EXPECT_NO_THROW(*sp2.begin());
        EXPECT_THROW(*++sp2.begin(), std::out_of_range&); // 1 shape kell legyen bent
    } ENDM
    
    TEST(Screen, drawing) {
        std::ifstream fs("snake_level.txt");
        ShapeParser sp3(fs);
        EXPECT_TRUE(fs.eof());
        Screen screen(100, 80);
        for (const Shape& s: sp3)
            screen.draw_shape(s);
        std::stringstream ss;
        ss << screen;
        const char* expected =
            "                                                                                                    \n"
            "                                                                                                    \n"
            "                                                                                                    \n"
            "                                                                                                    \n"
            "█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n"
            "█                                                                                                  █\n"
            "█                                                                                                  █\n"
            "█                                                                                                  █\n"
            "█                                               █▄▄                                                █\n"
            "█                                               █████▄                                             █\n"
            "█                                               ████████▄                                          █\n"
            "█                                               ██████▀▀                                           █\n"
            "█                                               ███▀                                               █\n"
            "█                                               ▀                                                  █\n"
            "█                                                                                                  █\n"
            "█                                                                                                  █\n"
            "█                ███▄                                                                              █\n"
            "█               █████                                                                              █\n"
            "█                ▀▀▀▀                                                                              █\n"
            "█                                                                                                  █\n"
            "█                                                                                                  █\n"
            "█                                                                                                  █\n"
            "█                                                                                                  █\n"
            "█                                                                                                  █\n"
            "█                                                                            ▄▄▄▄███▄              █\n"
            "█                                                                          ▄██████████▄            █\n"
            "█                                                                          █████████████▄          █\n"
            "█                                                                         ▄█████████████           █\n"
            "█                                                                         ██████████████           █\n"
            "█                                                                          ▀███████████            █\n"
            "█                                                                            ▀██████▀▀▀            █\n"
            "█                                                                              ▀▀                  █\n"
            "█                                                                                                  █\n"
            "█                                                                                                  █\n"
            "█                                                                                                  █\n"
            "█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█\n"
            "                                                                                                    \n"
            "                                                                                                    \n"
            "                                                                                                    \n"
            "                                                                                                    \n";
        EXPECT_STREQ(expected, ss.str().c_str());
    } ENDM
    
    TEST(main_assignment, invalid) {
        std::stringstream in("0 0    79.9 49.9    50 60    70.5 36.234    10 15    15 20    234 asd");
        std::stringstream out;
        main_assignment(in, out);
        const char* expected =
            "Please give coordinates in the following form: \"x y\" (without quotes), or type something else to quit:\n"
            "No shapes were found that have point Vector(0, 0).\n"
            "4-gon(center = Vector(40, 89.5), vertex = Vector(0, 49.5)) has point Vector(79.9, 49.9).\n"
            "4-gon(center = Vector(104.5, 25), vertex = Vector(79.5, 0)) has point Vector(79.9, 49.9).\n"
            "4-gon(center = Vector(40, 89.5), vertex = Vector(0, 49.5)) has point Vector(50, 60).\n"
            "6-gon(center = Vector(65, 37), vertex = Vector(60.7, 32.7)) has point Vector(70.5, 36.234).\n"
            "No shapes were found that have point Vector(10, 15).\n"
            "Circle(center = Vector(15.1, 20.85), radius = 2.05) has point Vector(15, 20).\n";
        EXPECT_STREQ(expected, out.str().c_str());
    } ENDM
    
    TEST(main_assignment, eof) {
        std::stringstream in("0 0    79.9 49.9    50");
        std::stringstream out;
        EXPECT_THROW(main_assignment(in, out), std::runtime_error&);
        const char* expected =
            "Please give coordinates in the following form: \"x y\" (without quotes), or type something else to quit:\n"
            "No shapes were found that have point Vector(0, 0).\n"
            "4-gon(center = Vector(40, 89.5), vertex = Vector(0, 49.5)) has point Vector(79.9, 49.9).\n"
            "4-gon(center = Vector(104.5, 25), vertex = Vector(79.5, 0)) has point Vector(79.9, 49.9).\n";
        EXPECT_STREQ(expected, out.str().c_str());
    } ENDM
}
