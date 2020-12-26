#ifndef TRIANGLEBINARY_TREE_H
#define TRIANGLEBINARY_TREE_H

#include "Graph.h"
#include "Binary_tree.h"
struct TriangleBinaryTree : BinaryTree{
public:
    TriangleBinaryTree(int l, int start_bottom = 0) : BinaryTree(l, start_bottom) {}

private:
    void draw() const;
};

#endif