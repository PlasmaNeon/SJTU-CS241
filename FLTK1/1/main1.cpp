
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "hyperelliptic.h"
#include <iostream>
//------------------------------------------------------------------------------

int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib

    Point tl(100,100);           // to become top left  corner of window

    Simple_window win(tl,600,400,"Canvas");    // make a simple window

//    Polygon poly;                // make a shape (a polygon)
//
//    poly.add(Point(300,200));    // add a point
//    poly.add(Point(350,100));    // add another point
//    poly.add(Point(400,200));    // add a third point
//
//    poly.set_color(Color::red);  // adjust properties of poly
//
//    win.attach (poly);           // connect poly to the window

    double a, b;
    int m, n, N;
    std::cin >> a >> b >> m >> n >> N;
    Hyperellipse hyper_e(a, b, m, n, N);
    hyper_e.set_color(Color::blue);
    win.attach(hyper_e);

    win.wait_for_button();       // give control to the display engine
    return 0;
}

//------------------------------------------------------------------------------
