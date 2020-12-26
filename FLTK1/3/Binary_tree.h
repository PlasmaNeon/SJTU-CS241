#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "Graph.h"
#include <cmath>
const int CANVAS_X = 1000;
const int CANVAS_Y = 1400;

struct BinaryTree : Graph_lib::Shape{
public:
    BinaryTree() : levels(0){}

    BinaryTree(int l, int start_bottom = 0):levels(l), start_bottom(start_bottom){
        totals = pow(2, l) - 1;
        linespace = 50;
        width = CANVAS_X;
        elems.resize(totals);
        if (levels != 0)
            placePoints();
    }

    virtual void draw () const;
    void setLinespace(int x) {linespace = x;}
    void setWidth(int x) {width = x;}
    void setStartBottom(int x){start_bottom = x;}

protected:
    int levels;
    int totals;
    vector<Point> elems;

    int linespace;
    int width;
    int start_bottom;
    void draw_lines() const;
    void placePoints();
};

#endif