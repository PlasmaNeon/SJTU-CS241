# include "Graph.h"
# include <vector>
# include <cmath>

using namespace Graph_lib;

struct Hyperellipse : Shape {
private:
    double a, b;
    int m, n;
    int N;
    Point center;

    void addPoints();
    void draw_lines() const;

public:
    Hyperellipse(double a, double b, int m, int n, int N, Point center = Point(300, 200)) :
        a(a), b(b), m(m), n(n), N(N), center(center) {
            addPoints();
    }

};