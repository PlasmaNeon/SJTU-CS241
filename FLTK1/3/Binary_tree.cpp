#include "Binary_tree.h"
#include <cmath>

void BinaryTree::placePoints() {
    // level = 1

    int y = start_bottom + linespace * (levels + 1);
    int min_step = width / (pow(2, levels - 1) + 2);
    // level >= 2
    for (int l= levels; l >= 1; l--) { // i-th level [2, levels]
        y -= linespace;
        for (int j = pow(2, l - 1) - 1; j <= pow(2, l) - 2; ++j) {
            int j_start = pow(2, l - 1) - 1;
            int x;
            if (l == levels)
                x = min_step + (j - j_start) * min_step;
            else
                x = (elems[j * 2 + 1].x + elems[j * 2 + 2].x) / 2;
            elems[j] = Point(x, y);
            // each level j = 2^(i-1) points,
            // index [2^(i-1)-1, 2^i-2]
        }
    }
}

void BinaryTree::draw_lines() const{
    for (int l = 1; l <= levels - 1; ++l){
        for (int j = pow(2, l - 1) - 1; j <= pow(2, l) - 2; ++j){
            Point parent = elems[j];
            Point child1 = elems[2 * j + 1];
            Point child2 = elems[2 * j + 2];
            fl_line(parent.x, parent.y, child1.x, child1.y);
            fl_line(parent.x, parent.y, child2.x, child2.y);
            draw();
        }
    }
}

void BinaryTree::draw() const{
    vector<Graph_lib::Circle> circles;
    int r = 8;
    for (int i = 0; i < elems.size(); ++i)
        fl_arc(elems[i].x - r, elems[i].y - r, r + r, r + r, 0, 360);
}