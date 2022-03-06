#include "shapes.hpp"

Segment Polygon::closest_edge_to(Vector p) const { // returns in positive direction: seg.b is "more" in the positive dir then a
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
