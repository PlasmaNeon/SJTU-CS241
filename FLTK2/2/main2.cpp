
//
// This is example code from Chapter 12.3 "A first example" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include <chrono>
#include "AnalogClock.h"
#include <iostream>
#include "unistd.h"
//------------------------------------------------------------------------------

int main()
{
    using namespace Graph_lib;   // our graphics facilities are in Graph_lib

    Point tl(100, 100);           // to become top left  corner of window

    Simple_window win(tl, 1800, 1200, "Canvas");    // make a simple window

    AnalogClock ac(Point(900, 600), 400);
    int n = 3;
    win.attach(ac.face.outer);
    for (int i = 0; i < 12; i++)
        win.attach(*ac.face.nums[i]);
    for (int i = 0; i < 60; ++i) {
        if (i % 5 == 0) continue;
        win.attach(*ac.face.dashes[i]);
    }
    win.attach(ac.digital_time);
    win.attach(ac.digital_date);
    win.attach(ac.s_hand);
    win.attach(ac.m_hand);
    win.attach(ac.h_hand);
    while (Fl::wait()) {
        ac.getTime();
        ac.updateDigital();
        ac.updateHand();
        win.redraw();
    }
}

//------------------------------------------------------------------------------
