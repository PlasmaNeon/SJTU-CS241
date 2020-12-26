//
#ifndef BARCHART_H
#define BARCHART_H
#include <fstream>
#include "Graph.h"

struct ChartLegend {
    Graph_lib::Rectangle rec;
    Graph_lib::Text txt;
    ChartLegend(Point upper_left, string s) :
            rec(upper_left, 30, 30), txt(Point(upper_left.x + 50, upper_left.y + 20), s){
        txt.set_font_size(15);
    }
};

class BarChart {
public:
    BarChart(Point upper_left, int x_len, int y_len) : x_len(x_len), y_len(y_len), upper_left(upper_left),
        x(Graph_lib::Axis::x, Point(upper_left.x, upper_left.y + y_len), x_len, 24, "Months"),
        y(Graph_lib::Axis::y, Point(upper_left.x, upper_left.y + y_len), y_len, 2, "Average Temperature"),
        title(Point(upper_left.x, upper_left.y), "Bar Chart: Average Temperature of Austin and New York in 2016"),
        as_legend(Point(upper_left.x + x_len, upper_left.y + 50), "Austin"),
        ny_legend(Point(upper_left.x + x_len, upper_left.y + 100), "New York"),
        as(12), ny(12){
        // Chart original Point in (upper_left.x, upper_left.y + y_len)
        title.move(x_len / 4, -50);
        title.set_font_size(30);

        as_legend.rec.set_fill_color(Graph_lib::Color::dark_green);
        ny_legend.rec.set_fill_color(Graph_lib::Color::cyan);

        x.label.move(3 * x_len / 4, 0);
        x.label.set_font_size(20);
        y.label.set_font_size(20);

        ifstream in_au("../Austin.csv");
        if (!in_au)
            error("Open file failed.");
        inputData_(in_au, Austin);
        ifstream in_ny("../NewYork.csv");
        inputData_(in_ny, NewYork);
        const vector<int> days{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        for (int i = 0; i < 12; ++i){
            as[i] = as[i] / days[i];
            ny[i] = ny[i] / days[i];
        }
        as_rec = vector<Graph_lib::Rectangle*>(12);
        ny_rec = vector<Graph_lib::Rectangle*>(12);
        as_text = vector<Graph_lib::Text*>(12);
        ny_text = vector<Graph_lib::Text*>(12);
        x_months = vector<Graph_lib::Text*>(12);
        const int ZOOM = 30;
        for (int i = 0; i < 12; ++i){
            as_rec[i] = new Graph_lib::Rectangle(Point(upper_left.x + i * x_len / 12, upper_left.y + y_len - as[i] * ZOOM), x_len / 24, as[i] * ZOOM);
            as_rec[i]->set_fill_color(Graph_lib::Color::dark_green);
            string text = to_string(as[i]);
            text.erase(text.size() - 4);
            as_text[i] = new Graph_lib::Text(Point(upper_left.x + i * x_len / 12, upper_left.y + y_len - as[i] * ZOOM), text);
            as_text[i]->set_font_size(15);

            ny_rec[i] = new Graph_lib::Rectangle(Point(upper_left.x + x_len / 24 + i * x_len / 12, upper_left.y + y_len - ny[i] * ZOOM), x_len / 24, ny[i] * ZOOM);
            ny_rec[i]->set_fill_color(Graph_lib::Color::cyan);
            text = to_string(ny[i]);
            text.erase(text.size() - 4);
            ny_text[i] = new Graph_lib::Text(Point(upper_left.x + + x_len / 24 + i * x_len / 12, upper_left.y + y_len - ny[i] * ZOOM), text);
            ny_text[i]->set_font_size(15);

            x_months[i] = new Graph_lib::Text(Point(upper_left.x + x_len / 12 * i + x_len / 24 , upper_left.y + y_len + 20), to_string(i + 1));
            x_months[i]->set_font_size(15);
        }


    }

    int x_len;
    int y_len;
    Point upper_left;
    Graph_lib::Axis x;
    vector<Graph_lib::Text*> x_months;
    Graph_lib::Axis y;
    Graph_lib::Text title;

    ChartLegend as_legend;
    ChartLegend ny_legend;

    vector<Graph_lib::Rectangle*> as_rec;
    vector<Graph_lib::Rectangle*> ny_rec;
    vector<Graph_lib::Text*> as_text;
    vector<Graph_lib::Text*> ny_text;


    enum City {Austin, NewYork};
    vector<double> as, ny;
private:
    void inputData_(ifstream& in, City c);
};



#endif