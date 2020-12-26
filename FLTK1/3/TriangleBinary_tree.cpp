#include "TriangleBinary_tree.h"

void TriangleBinaryTree::draw() const {
    int r = 10;
    for (int i = 0; i < elems.size(); ++i){
        const int &x = elems[i].x;
        const int &y = elems[i].y;
        Point p1(x, y - r);
        Point p2(x - r * pow(3.0, 1 / 2) / 2, y + r / 2);
        Point p3(x + r * pow(3.0, 1 / 2) / 2, y + r / 2);
        fl_line(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
        fl_line(p3.x, p3.y, p1.x, p1.y);
    }
}