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
    double coefficient = 0;
    int index = 0;
    int saved_symbol = 1;
    // Check all polynomial string
    //cout << "s = " << s << endl;
    while (i < len && isvalid){
        // meet '+' / '-', calculate prev.
        if(s[i] == '+' || s[i] == '-' ){
            if (fabs(coefficient) > 0.00001)
              saved[index] += coefficient;
            if (fabs(saved[index]) < 0.00001)
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

        /* Process coefficient */
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

double Polynomial::getValue(double x){
    double ans = 0;
    for (auto &i : saved){
        ans += i.second * pow(x, i.first);
        //std::cout << "ans =" <<ans<<endl;
    }
    return ans;
}

void Polynomial::print(map<int, double> &m){
    cout << noshowpos;
    for (auto x = m.rbegin(); x != m.rend() ; x++){
        if (x!= m.rbegin())
            cout << showpos;
        if (x->first == 0){
            // if index = 0, const number
            int tmp = x->second * 10000;
            cout << fixed << setprecision(4) << ((double)tmp) / 10000;
        }
        else {
            // if index != 0
            // if coefficient = 1
            // if (fabs(x->second - 1) <= 1e-6) {
            //   if(x!=m.rbegin())
            //     cout << '+';
            // }
            // else if (fabs(x->second +1) <= 1e-6)
            //     cout << '-';
            // else cout << fixed << setprecision(4) << x->second;
            int tmp = x->second * 10000;
            cout << fixed << setprecision(4) << ((double)tmp) / 10000;
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

void Polynomial::printValueAtX(double x){
    if (!isvalid)
        cout << "error" << endl;
    else {
        double val = getValue(x);
        string str = to_string(val);
        int len = str.length();
        str.erase(len - 2);
        cout << str << endl;
        //int tmp = val * 10000;
        //cout << tmp <<endl;
        //cout << noshowpos << fixed << setprecision(4) << ((double)tmp) / 10000 << endl;
        //cout << noshowpos << fixed << setprecision(4) << val << endl;
    }

}

void div(Polynomial &diviend, Polynomial &divisor, 
            map<int, double> &res, map<int, double> &remain){
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
    //cout << "divisor_hi" << divisor_hi->first <<endl;
    map<int, double> r; //save remain
    r = diviend.saved;
    auto r_hi = r.rbegin();
    while ( !r.empty() && r_hi->first >= divisor_hi->first){
        double co_ = r_hi->second / divisor_hi->second; //Calculate coefficient multiple
        int index_ = r_hi->first - divisor_hi->first;  //Calculate index multiple
        //cout << "co_ = " << co_ <<" index_ =" << index_ <<endl;
        if (index_ >=0){
            res[index_] = co_;  //Save to result
    
          // Calculate remain
          for (auto x = divisor.saved.rbegin(); x != divisor.saved.rend(); x++){
              r[x->first + index_] -= x->second * co_;
              if (r.count(x->first + index_) && r[x->first + index_] == 0) 
                  r.erase(x->first + index_);
          }
          
        }
        else break;
        //printMap(r);
        if (!r.empty())
          r_hi = r.rbegin();  //Highest index pointer in remain
    }
    //cout<<"here";
    if (r.empty())
      remain[0] = 0;
    else remain = r;
}

void printMap(const map<int, double> &m){
    cout << noshowpos;
    for (auto x = m.rbegin(); x != m.rend() ; x++){
        if (x!= m.rbegin())
            cout << showpos;
        if (fabs(x->first) <= 1e-6){
            // if index = 0, const number
            int tmp = x->second * 10000;
            cout << fixed << setprecision(4) << (double)tmp / 10000.0;
        }
        else {
            // if index != 0
            // if coefficient = 1
            // if (fabs(x->second - 1) <= 1e-6) {
            //   if(x!=m.rbegin())
            //     cout << '+';
            // }
            // else if (fabs(x->second +1) <= 1e-6)
            //     cout << '-';
            // else cout << fixed << setprecision(4) << x->second;
            int tmp = x->second * 10000;
            cout << fixed << setprecision(4) << (double)tmp / 10000;
            cout << 'x'; 
            if (x->first != 1)
                cout << '^' << to_string(x->first);
            
        }
    }
    cout << endl;
}