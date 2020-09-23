#include "Polynomial.h"
#include <cmath>
#include "std_lib_facilities.h"
#include <vector>

using namespace std;


Polynomial::Polynomial(string s){
    if (isdigit(s[0]) || s[0] == 'x') s = '+' + s;
    s = s + '+';
    int len = s.length();
    int i = 0;
    isvalid = true;
    float coefficient = 0;
    int index = 0;
    int saved_symbol = 1;
    // Check all polynomial string chars
    while (i < len && isvalid){
        // meet '+' / '-', calculate prev.
        if(s[i] == '+' || s[i] == '-' ){
            if (fabs(coefficient) > 0.00001) 
                // coefficienrt != 0
                saved[index] += coefficient;
            if (fabs(saved[index]) < 0.00001)
                // coefficient == 0, remove from map.
                saved.erase(index);
            if (s[i] == '+') coefficient = 1;
            if (s[i] == '-') coefficient = -1;
            i++;
            index = 0;
        }
        else {
            isvalid = false;
            break;
        }

        // Reach ends of string.
        if (i >= len) break;
        while (s[i] == '+')
            ++i;
        if (!(isdigit(s[i]) || s[i] == 'x')){
            isvalid = false;
            break;
        }

        // Process coefficient.
        if (s[i] == 'x'){
            coefficient *= 1.0;
        }
        else if (isdigit(s[i])){
            string num_s = ""; 
            bool use_point = false;
            while(isdigit(s[i]) || s[i] == '.'){
                if (!isValidChar(s[i])){
                    isvalid = false;
                    break;
                }
                num_s += s[i];
                if (s[i] == '.'){
                    //Check if point is used.
                    if (use_point || i + 1 >= len || !isdigit(s[i + 1]) ){
                        isvalid = false;
                        break;
                    }
                    else use_point = true;
                }
                i++;
            }
            coefficient *= stod(num_s);
        }
        else {
            isvalid = false;
            break;
        }

        //Check if x exists, process index
        index = 0;
        if (s[i] == 'x'){
            // index >= 2
            if (s[i + 1] == '^'){
                i += 2;
                string index_s = "";
                while (isdigit(s[i])){
                    index_s += s[i];
                    i++;
                }
                if (index_s == "") {
                    isvalid = false;
                    break;
                }
                if (i < len && !(s[i] == '+' || s[i] == '-')) {
                    isvalid = false; 
                    break;
                }
                index = stoi(index_s);
            }
            // index == 1
            else if (s[i + 1] == '+' || s[i + 1] == '-'){
                index = 1;
                i++;
            }
            //invalid char
            else isvalid = false;
        }
        else if (s[i] == '+' || s[i] == '-')
            // index == 0
            index = 0;
        else isvalid = false;
    }
}

void Polynomial::derivation(){
    for (auto &x : saved){
        if (x.first == 0){
            continue;
        }
        der[x.first - 1] = x.first * x.second;
    }
}

float Polynomial::getValue(float x){
    float ans = 0;
    for (auto &i : saved){
        ans += i.second * pow(x, i.first);
    }
    return ans;
}

float getValue(map<int, float>& m, float x){
    float ans = 0;
    for (auto &i : m){
        ans += i.second * pow(x, i.first);
    }
    return ans;
}

void Polynomial::print(map<int, float> &m){
    cout << noshowpos;
    for (auto x = m.rbegin(); x != m.rend(); x++){
        if (x != m.rbegin())
            cout << showpos;
        if (x->first == 0){
            // if index = 0, const number
            int tmp = x->second * 10000;
            cout << fixed << setprecision(4) << ((float)tmp) / 10000;
        }
        else {
            int tmp = x->second * 10000;
            cout << fixed << setprecision(4) << ((float)tmp) / 10000;
            cout << 'x'; 
            if (x->first != 1)
                cout << '^' << to_string(x->first);
            
        }
    }
    cout << endl;
}

void Polynomial::printDerivation(){
    if(!isvalid){
        cout << "error" << endl;
        return;
    }
    derivation();
    if (der.empty())
        cout << "0.0000" << endl;
    else
        print(der);
}

void Polynomial::printPolynomial(){
    if(!isvalid){
        cout << "error" << endl;
        return;
    }
    if (saved.empty())
        cout << "0.0000" << endl;
    else
        print(saved);
}

void Polynomial::printValueAtX(float x){
    if (!isvalid)
        cout << "error" << endl;
    else {
        float val = getValue(x);
        string str = to_string(val);
        int len = str.length();
        str.erase(len - 2);
        cout << str << endl;
    }
}

void div(Polynomial &diviend, Polynomial &divisor, 
            map<int, float> &res, map<int, float> &remain){
    if (divisor.saved.empty()){
        cout << "error" <<endl << "error" << endl;
        return;
    }
    if (diviend.saved.empty()){
        res[0] = 0;
        remain[0] = 0;
        return;
    }

    auto divisor_hi = divisor.saved.rbegin(); // Highest index pointer in divisor
    map<int, float> r; //save remain
    for (auto x :diviend.saved)
        r[x.first] = (float) x.second;
    auto r_hi = r.rbegin();
    if (r_hi->first < divisor_hi->first){
        res[0] = 0;
        remain = r;
        return;
    }
    while (!r.empty() && r_hi->first >= divisor_hi->first){
        float co_ = r_hi->second / divisor_hi->second; //Calculate coefficient multiple
        int index_ = r_hi->first - divisor_hi->first;  //Calculate index multiple
        if (index_ >=0){
            res[index_] = co_;  //Save to result
            // Calculate remain
            for (auto x = divisor.saved.rbegin(); x != divisor.saved.rend(); x++){
                r[x->first + index_] -= x->second * co_;
                if (r.count(x->first + index_) && fabs(r[x->first + index_]) <= 1e-6) 
                    r.erase(x->first + index_);
            }
        }
        else break;
        if (!r.empty())
          r_hi = r.rbegin();  //Highest index pointer in remain
    }
    if (r.empty())
        remain[0] = 0;
    else remain = r;
}

void printMap(const map<int, float> &m){
    cout << noshowpos;
    for (auto x = m.rbegin(); x != m.rend() ; x++){
        // Process coefficient
        string str = to_string(x->second);
        int len = str.length();
        str.erase(len - 2);
        if (x != m.rbegin()){
            if (x->second > 0)
                str = '+' + str;
        }
        if (x->first != 0){
            cout << str;
            cout << 'x'; 
            if (x->first != 1)
                cout << '^' << to_string(x->first);
        }
        else {
            //Const number
            cout << str;
        }
    }
    cout << endl;
}

bool ensureSecondDerivativeExists(Polynomial &p){
    int max_index = p.saved.rbegin()->first;
    if (max_index <= 1) return false;
    return true;
}




map<int, float> calcDerivation(const map<int, float>& m){
    map<int, float> derivation;
    for (auto& x : m){
        if (x.first == 0)
            continue;
        derivation[x.first - 1] = x.first * x.second;
    }
    return derivation;
}

bool newton(Polynomial& f, float a, float b,
            float& ans){     // Output: ans
    // Requires first derivation ans second derivation calculated in main().

    //Ensure f(a)f(b) < 0
    float fa = getValue(f.saved, a);
    float fb = getValue(f.saved, b);
    if (fa * fb < 0){}
    else {
        //cout << "error1" << endl;
        return false;
    }

    // Ensure a-f(a)/f'(a) <= b && b-f(b)/f'(b) >= a
    float f1a = getValue(f.der, a);
    float f1b = getValue(f.der, b);
    float f2a = getValue(f.der2, a);
    float f2b = getValue(f.der2,b);
    if (f1a * f1b > 0 && f2a * f2b > 0 &&
        ((a - fa/f1a) <= (b + 1e-7)) && ((b - fb/f1b) >= (a + 1e-7))){}
    else {
        return false;
    }

    
    float x = a + (b - a) / 2;

    int times = 10000;
    float x_tmp, f1x_tmp, f2x_tmp;
    f1x_tmp = getValue(f.der, x);
    f2x_tmp = getValue(f.der2, x);
    while (times > 0){
        float fx = getValue(f.saved, x);
        float f1x = getValue(f.der, x);
        float f2x = getValue(f.der2, x);
        //cout << "x" << x << " fx" << fx << " f1x" << f1x << " f2x" << f2x << endl;
    
        // Compare and check condition
        if (!(f1x_tmp * f1x > 0 && f2x_tmp * f2x > 0))
            return false;

        if (fabs(fx / f1x) <= 1e-7){
            ans = x;
            return true;
        }
        // Update x
        x = x - fx / f1x;
        times--;

        // Save current vals.
        x_tmp = x;
        f1x_tmp = f1x;
        f2x_tmp = f2x;
    }    

    return false;
}

void printFloat4c(float x){
    string str = to_string(x);
    int len = str.length();
    str.erase(len - 2);
    cout << str << endl;
}