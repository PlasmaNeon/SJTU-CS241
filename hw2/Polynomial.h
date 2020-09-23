#include <map>
#include "std_lib_facilities.h"
using namespace std;
class Polynomial{

public:
    map<int, float> saved;
    map<int, float> der;
    map<int, float> der2;
    bool isvalid;

    Polynomial(string s);
    float getValue(float x);
    void printDerivation();
    void printPolynomial();
    void printValueAtX(float x);
    

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
    void print(map<int, float>& m);
    void derivation();
};

void printMap(const map<int, float>& m);
map<int, float> calcDerivation(const map<int, float>& m);
float getValue(map<int, float>& m, float x);

void printFloat4c(float x);