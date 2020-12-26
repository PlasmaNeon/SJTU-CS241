
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "BarChart.h"

//------------------------------------------------------------------------------

int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib

    Point tl(100,100);           // to become top left  corner of window

    Simple_window win(tl,1800,1200,"Canvas");    // make a simple window

//    Polygon poly;                // make a shape (a polygon)
//
//    poly.add(Point(300,200));    // add a point
//    poly.add(Point(350,100));    // add another point
//    poly.add(Point(400,200));    // add a third point
//
//    poly.set_color(Color::red);  // adjust properties of poly
//
//    win.attach (poly);           // connect poly to the window

    BarChart bc(Point(100, 100), 1200, 1000);
    win.attach(bc.x);
    win.attach(bc.y);
    win.attach(bc.title);
    win.attach(bc.as_legend.rec);
    win.attach(bc.as_legend.txt);
    win.attach(bc.ny_legend.rec);
    win.attach(bc.ny_legend.txt);
    for (int i = 0; i < 12; ++i) {
        win.attach(*bc.as_rec[i]);
        win.attach(*bc.as_text[i]);
        win.attach(*bc.ny_rec[i]);
        win.attach(*bc.ny_text[i]);
        win.attach(*bc.x_months[i]);
    }
    win.wait_for_button();       // give control to the display engine
}

//------------------------------------------------------------------------------
