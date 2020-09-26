#include "std_lib_facilities.h"
#include <vector>
#include <map>
#include <set>

class LinearEquations{
public:
    vector< map<int, double> > co;
    //vector<double> r;
    set<int> x_nums; // saves how many x_num is used.
    bool isvalid;
    int eqs_num;
    LinearEquations();
    //void getInput();

    friend void printEqs(LinearEquations& eqs);
    friend void printRight(LinearEquations& eqs);
    friend bool gauss(LinearEquations& eqs, map<int, double>& ans);
private:
    bool checkValid(string s, map<int, double>& output);
    bool isValidChar(char c){
        if (isdigit(c) || c == '.' || c == '+' || c == '_' || c == '-' || c == 'x')
            return true;
        else return false;
    }
};

void printAns(map<int, double>& ans);
void printEq(map<int, double>& eq);