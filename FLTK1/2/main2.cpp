
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "righttriangle.h"
#include <iostream>
//------------------------------------------------------------------------------

int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib

    Point tl(100,100);           // to become top left  corner of window

    Simple_window win(tl,600,400,"Canvas");    // make a simple window


    RightTriangle rt(200, 200, 50, 50);
    rt.set_color(Color::blue);
    rt.set_fill_color(9);
    //win.attach(rt);
    RegularOctagon ro(rt);


    vector<RightTriangle> parts(8, rt);
    int a = rt.getA();
    constexpr double pi = 3.1416;

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

    for (int i = 0; i < 8; ++i)
        win.attach(parts[i]);

    win.wait_for_button();       // give control to the display engine
}

//------------------------------------------------------------------------------
