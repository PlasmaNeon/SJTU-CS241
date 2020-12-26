
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "Binary_tree.h"
#include "TriangleBinary_tree.h"
#include <iostream>
//------------------------------------------------------------------------------



int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib

    Point tl(100,100);           // to become top left  corner of window

    Simple_window win(tl, CANVAS_X, CANVAS_Y,"Canvas");    // make a simple window

    int n;
    std::cin >> n;
    BinaryTree bst(n);
    bst.set_color(1);
    win.attach (bst);           // connect poly to the window

    TriangleBinaryTree tbst(n, 500);
    tbst.set_color(Color::dark_green);
    win.attach (tbst);
    win.wait_for_button();       // give control to the display engine
}

//------------------------------------------------------------------------------
