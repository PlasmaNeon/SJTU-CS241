#include "LinearEquations.h"
#include "std_lib_facilities.h"
#include <map>
#include <set>

LinearEquations:: LinearEquations(){
    string str;
    int x_num_max = 0;  // Saves the maximum nums 
    map<int, double> output;  // int: saves the number of x_n, 
                              //double: saves the coefficient of x_n
    int eqs_num = 0;
    isvalid = true;
    while(getline(cin, str)){
        output.clear();
        if (str =="") 
            break;
        if (isvalid){
            isvalid = checkValid(str, output);
            if (isvalid){
                output[0] += 0;
                x_nums.insert(0);
                if (output.size() == 1){
                    isvalid = false;
                    break;
                }
                // output[0] Saves const vals. 
                co.push_back(output);
                eqs_num++;
            }
            //printEq(output);
        }
        
    }
    
    if (isvalid){ 
        if (x_nums.size() - 1 > eqs_num)
            isvalid = false;
    }


}


bool LinearEquations::checkValid(string s, map<int, double>& output){
    
    int i = 0;
    bool use_eq = false;
    double coefficient = 0;
    int x_n = 0;
    
    if (isdigit(s[0]) || s[0] == 'x') s = '+' + s;
    int p;
    for (p = 0; p < s.length() && s[p] != '='; p++){}
    s.erase(p,1);
    if(isdigit(s[p]) || s[p] == 'x')
        s.insert(p,1,'+');
    
    for (; p < s.length(); p++){
        if (s[p] == '+') s.replace(p,1,"-");
        else if (s[p] == '-') s.replace(p,1,"+");
        else if (s[p] == '=') return false;
    }
    s = s + '+';
    //cout << s <<endl;
    //Process left part.
    int len = s.length();
    while (i < len){
        // meet '+' / '-', calculate prev
        if (s[i] == '+' || s[i] == '-' || s[i] =='='){
            if (fabs(coefficient) > 1e-6){
                //coefficient != 0
                output[x_n] += coefficient;
                x_nums.insert(x_n);
            }
            if (fabs(output[x_n]) < 1e-6){
                //coefficient ==0, remove from map
                output.erase(x_n);
                x_nums.erase(x_n);
            }
            // prepare for current coefficient pos/neg
            if (s[i] == '+') coefficient = 1;
            if (s[i] == '-') coefficient = -1;
            i++;
        } else return false;
    
        if (i == len) break;
        
        if (!(isdigit(s[i]) || s[i] =='x'))
            return false;
        

        if (s[i] == 'x'){
            coefficient *= 1.0;
        }
        else if (isdigit(s[i])){
            string co_s;
            bool use_point = false;
            while (isdigit(s[i]) || s[i] =='.'){
                if (!isValidChar(s[i]))
                    return false;
                co_s += s[i];
                if (s[i] == '.'){
                    //Check if point is used.
                    if (use_point || i + 1 >= len || !isdigit(s[i + 1]))
                        return false;
                    else use_point = true;
                }
                i++;
            }
            coefficient *= stod(co_s);
        } else return false;

        x_n = 0;
        if (s[i] == 'x' && s[i + 1] == '_'){
            i += 2;
            string xn_s;
            while (isdigit(s[i])){
                xn_s += s[i];
                i++;
            }
            if (!(s[i] == '+' || s[i] == '-' ))
                return false;
            x_n = stoi(xn_s);
        
            
        } else if (s[i] == '+' || s[i] == '-' ){
            x_n = 0;
        }else return false;

    }
    return true;
}


void printEqs(LinearEquations& eqs){
    for (auto& v : eqs.co){
        for (auto& kv : v){
            if (kv.first == 0) cout<< kv.second <<' ';
            else cout << kv.second <<"x_" << kv.first << ' ';
        }
        cout <<endl;
    }
}


bool mycomp(map<int, double>& m1, map<int, double>& m2){
    if (m1.size() > m2.size()) return true;
    if (next(m1.begin(), 1)->first < next(m2.begin(), 1)->first) return true;
    return false;
}

bool gauss(LinearEquations& eqs, map<int, double>& ans){
    vector<map<int, double>>& co = eqs.co;
    //vector<double>& r = eqs.r;
    sort(co.begin(), co.end(), mycomp);
    int size = co.size();
    for (int i = 0; i < size; i++){
        if (co[i][0] != 0)
            co[i][0] = -co[i][0];
        
    }
    printEqs(eqs);

    int i,j;
    for (i = 0; i < size - 1; i++){ 
         //#i equations as subtractend
        if (co[i].empty()) continue;
        int subtratend_smallest_xn = next(co[i].begin(), 1)->first;
        for (j = i + 1; j < size; j++){
            // # j [i+1, size-1] as subtractor
            int subtractor_smallest_xn = next(co[j].begin(), 1)->first;
            if (subtractor_smallest_xn > subtratend_smallest_xn){
                continue;
            }
            //if (next(a.begin(), 1)->second == 0) return false;
            double tmp = next(co[j].begin(), 1)->second / next(co[i].begin(), 1)->second;
            for (auto& kv : co[i]){    
                co[j][kv.first] = co[j][kv.first] - tmp * co[i][kv.first];
                if (fabs(co[j][kv.first]) < 1e-6 && kv.first != 0) 
                    co[j].erase(kv.first); 
            }
            if (co[j].size() == 1) {
                if (co[j][0] != 0)
                    return false;
            }
        }
    }
    
    for (auto kv : co){
        if (kv.size() == 0) {
                eqs.eqs_num--;
                if (eqs.x_nums.size() - 1 > eqs.eqs_num)
                    return false;
            }
    }

    for (int i = size - 1; i >= 0; i--){
        if (co[i].size() == 0){
        }
        else if (co[i].size() == 1) {
            if (co[i][0] == 0) continue;
            else return false;
        }
        else if (co[i].size() == 2){
            ans[next(co[i].begin(), 1)->first] = co[i][0] / next(co[i].begin(), 1)->second;
            //next(co[i].begin(), 1)->second = 1;
        }
        else{
            double tmp_sum = 0;
            for (auto& kv : co[i]){
                //kv.first = x_n
                //kv.second = coefficient
                //ans[x_n] saves the val of x_n
                tmp_sum += ans[kv.first] * kv.second;
            }
            ans[next(co[i].begin(), 1)->first] = (co[i][0] - tmp_sum) / next(co[i].begin(), 1)->second;
        }
    }

    return true;
}

void printAns(map<int, double>& ans){
    for (auto& kv : ans){
        if (kv.first == 0 ) continue;
        string s = to_string(kv.second);
        int len = s.length();
        s.erase(len - 2);
        //cout << "x_" << kv.first << "=" << s;
        if (s == "-0.0000") cout << "0.0000";
        else cout << s;
        if (kv != *ans.end()) cout <<' ';
    }
    cout << endl;
}

void printEq(map<int, double>& eq){
    for (auto& kv : eq){
        cout << " x_" << kv.first << '=' << kv.second;
    }
    cout << endl;
}