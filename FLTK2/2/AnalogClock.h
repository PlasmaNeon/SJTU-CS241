//
#ifndef ANALOG_CLOCK_H
#define ANALOG_CLOCK_H
#include "Graph.h"
#include <chrono>
#include <iostream>
#include "unistd.h"
const double pi = 3.1416;

struct ClockFace {
    ClockFace(Point c, int r) : outer(c, r), center(c), rr(r), nums(12), dashes(60) {
        for (int i = 0; i < 12; ++i){
            nums[i] = new Graph_lib::Text(Point(center.x + 7 * r / 8 * cos((i - 2) * pi / 6), center.y + 7 * r / 8 * sin((i - 2) * pi / 6)), to_string(i + 1));
            nums[i]->set_font_size(15);
        }
        for (int i = 0; i < 60; ++i){
            if (i % 5 == 0) continue;
            Point dash_start, dash_end;
            dash_start.x = center.x + 7 * r / 8 * cos((i - 15) * 2 * pi / 60);
            dash_start.y = center.y + 7 * r / 8 * sin((i - 15) * 2 * pi / 60);
            dash_end.x = center.x + 8 * r / 9 * cos((i - 15) * 2 * pi / 60);
            dash_end.y = center.y + 8 * r / 9 * sin((i - 15) * 2 * pi / 60);
            dashes[i] = new Graph_lib::Line(dash_start, dash_end);
        }
    }

    Graph_lib::Circle outer;


    vector<Graph_lib::Text*> nums;
    vector<Graph_lib::Line*> dashes;

    Point center;
    int rr;
    ~ClockFace(){
        for (int i = 0; i < 12; ++i)
            delete nums[i];
        for (int i = 0; i < 60; ++i)
            if (dashes[i])
                delete dashes[i];
    }
};

struct ClockHand : Graph_lib::Shape{
    Point start;
    Point end;
    int len;
    ClockHand(Point start, int len, double theta = 0) : start(start), len(len){
        int rx = len * cos(theta);
        int ry = len * sin(theta);
        end.x = start.x + rx;
        end.y = start.y + ry;
    }

    void updateEnd(double theta){
        int rx = len * cos(theta);
        int ry = len * sin(theta);
        end.x = start.x + rx;
        end.y = start.y + ry;
    }

    void draw_lines() const override{
        fl_line_style(FL_SOLID, 10);
        fl_line(start.x, start.y, end.x, end.y);
    }
};

class AnalogClock{
public:

    AnalogClock(Point c, int r) : face(c, r),
                                  h_hand(c, r / 2), m_hand(c, 2 * r / 3), s_hand(c, 3 * r / 4),
                                  digital_time(c, ""), digital_date(c, ""),
                                  center(c), rr(r){

        getTime();
        updateDigital();

        digital_time.move(100, -20);
        digital_time.set_font_size(20);
        digital_date.move(100, 20);
        digital_date.set_font_size(20);

        h_hand.set_color(2);
        m_hand.set_color(3);
        s_hand.set_color(4);
    }

    ClockHand h_hand;
    ClockHand m_hand;
    ClockHand s_hand;
    ClockFace face;


    Graph_lib::Text digital_time;
    Graph_lib::Text digital_date;

    void getTime();

    void updateDigital();
    void updateHand();


    ~AnalogClock(){}
private:
    Point center;
    int rr;
    int h, m, s;
    int year, month, day;
};

#endif