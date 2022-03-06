#include "vectormath.hpp"

const Vector Vector::UP   ( 0, -1);
const Vector Vector::DOWN ( 0,  1);
const Vector Vector::LEFT (-1,  0);
const Vector Vector::RIGHT( 1,  0);

bool Segment::is_point_to_the_left(Vector p) const {
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
Vector Segment::closest_point_to(Vector p) const { // result is between a and b
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
