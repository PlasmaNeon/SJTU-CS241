#include "BarChart.h"

void BarChart::inputData_(ifstream& in, City c) {
    string line;
    getline(in, line);
    while (getline(in, line)){
        istringstream iss(line);
        string date;
        string data;
        getline(iss, date, ',');
        getline(iss, data, ',');
        string m;
        istringstream iss2(date);
        getline(iss2, m, '/');
        getline(iss2, m, '/');
        if (c == BarChart::Austin)
            as[stoi(m) - 1] += stod(data);
        else if (c == BarChart::NewYork)
            ny[stoi(m) - 1] += stod(data);

    }
}