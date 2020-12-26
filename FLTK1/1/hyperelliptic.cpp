# include "hyperelliptic.h"

void Hyperellipse ::addPoints() {
    double step = a * 4 / N;
    for (double x = -a; x <= a; x += step) {
        double y = pow(1 - pow(fabs(x / a), n), 1.0 / m) * b;
        add(Point(x + center.x, y + center.y));
        if(y != 0) add(Point(x + center.x, -y + center.y));
    }
}

void Hyperellipse :: draw_lines() const {
    if(color().visibility())
        for (int i = 0; i < number_of_points(); ++ i)
            for (int j = i + 1; j < number_of_points(); ++ j)
                fl_line(point(i).x, point(i).y, point(j).x, point(j).y);
}