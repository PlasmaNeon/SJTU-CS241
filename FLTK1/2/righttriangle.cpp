#include "righttriangle.h"
#include <cmath>

void RightTriangle::compose() {
    Point center = point(0);
    Point on_x(center.x + a, center.y);
    Point on_y(center.x, center.y + b);
    add(on_x);
    add(on_y);
}

void RightTriangle::rotate(double theta) {
    Point center = point(0);
    Point on_x = point(1);
    Point on_y = point(2);

    int ox_x = on_x.x - center.x;
    int ox_y = on_x.y - center.y;
    int oy_x = on_y.x - center.x;
    int oy_y = on_y.y - center.y;
    Point new_on_x(ox_x * cos(theta) - ox_y * sin(theta) + center.x,
                   ox_x * sin(theta) + ox_y * cos(theta) + center.y);
    Point new_on_y(oy_x * cos(theta) - oy_y * sin(theta) + center.x,
                   oy_x * sin(theta) + oy_y * cos(theta) + center.y);
    set_point(1, new_on_x);
    set_point(2, new_on_y);
}

void RegularOctagon::compose() {
    int a = tri_a;
    double pi = 3.1416;
    for (int i = 0; i < 8; i++)
        parts[i].set_fill_color(i + 1);
    parts[0].move(a, a);
    parts[1].move(0, a);
    parts[2].move(a, 3 * a);
    parts[3].move(a, 2 * a);
    parts[4].move(3 * a, 2 * a);
    parts[5].move(2 * a, 2 * a);
    parts[6].move(2 * a, a);
    parts[7].move(2 * a, 0);
    parts[0].rotate(pi);
    parts[1].rotate(0);
    parts[2].rotate(-pi / 2);
    parts[3].rotate(pi / 2);
    parts[4].rotate(pi);
    parts[5].rotate(0);
    parts[6].rotate(-pi / 2);
    parts[7].rotate(pi / 2);
}

void RegularOctagon::draw_lines() const {
    for (int i = 0; i < 8; ++i)
        parts[i].draw_lines();
}