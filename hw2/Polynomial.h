#include <map>
#include "std_lib_facilities.h"
using namespace std;
class Polynomial{

public:
    map<int, double> saved;
    map<int, double> der;
    map<int, double> der2;
    bool isvalid;

    Polynomial(string s);
    double getValue(double x);
    void printDerivation();
    void printPolynomial();
    void printValueAtX(double x);
    

    friend void div(Polynomial &diviend, Polynomial &divisor, // Input
                    map<int, float> &res, map<int, float> &remain); // Output

    friend bool checkNewtonValid(Polynomial &p, float l, float r);
    friend bool ensureSecondDerivativeExists(Polynomial &p);
    friend bool newton(Polynomial &f, float a, float b, float& ans);
private:
    

    bool isValidChar(char c){
        if (isdigit(c) || c == '.' || c == '+' || c == '^' || c == '-' || c == 'x')
            return true;
        else return false;
    }
    void print(map<int, double>& m);
    void derivation();
};

void printMap(const map<int, float>& m);
map<int, double> calcDerivation(const map<int, double>& m);
double getValue(map<int, double>& m, double x);

void printFloat4c(float x);