#include "Graph.h"
struct RightTriangle : Graph_lib::Closed_polyline{
public:
    RightTriangle(){}

    RightTriangle(int center_x, int center_y, int a, int b, double rotate_angle = 0) :
         a(a), b(b), rotate_angle(rotate_angle){
        add(Point(center_x, center_y));
        compose();
        if (!rotate_angle)
            rotate(rotate_angle);
    }

    RightTriangle(const RightTriangle& rt){
        for (int i = 0; i < rt.number_of_points(); ++i)
            add(rt.point(i));
    }

    void rotate(double theta);
    void move(int dx, int dy){
        for (int i = 0; i < number_of_points(); ++i)
            set_point(i, Point(point(i).x + dx, point(i).y + dy));
    }
    void setCenter(int new_x, int new_y){
        int dx = new_x - point(0).x;
        int dy = new_y - point(0).y;
        move(dx, dy);
    }

    int getA() const{ return a;}
    int getB() const {return b;}
    int getC() const{ return sqrt(a * a + b * b);}
private:
    int a, b;
    double rotate_angle;
    void compose();

};

struct RegularOctagon : RightTriangle{
    RegularOctagon() : tri_a(0){}
    RegularOctagon(const RightTriangle& base) {
        for (int i = 0; i < 8; ++i)
            parts.push_back(base);
        tri_a = base.getA();
    }
private:
    vector<RightTriangle> parts;
    int tri_a; //triangle right angle len.

    void compose();
    void draw_lines() const;
};