#include "std_lib_facilities.h"
//#include "Interpolation.h"
//#include "SimpleLinearRegression.h"
#include <map>
//定义main函数
int main()
{
    /********** Begin **********/
    bool exercisel = true;
    if (exercisel){
    //第一关执行代码 完成 Interpolation.cpp与 Interpolation.h文件
   		string str;          //测试输入数据存放变量
    	getline(cin,str);    //读取测试输入，并存入str
        size_t sz;
        bool valid = true;
        double x = stod(str, &sz);
        if (sz != str.length()) {
            valid = false;
            cout << "error" << endl;
            return 0;
        }
        map<double, double> input;
        while ( getline(cin, str)){
            if (str.size() == 0) break;
            if (valid){
                size_t index;
                double xx = stod(str, &index);
                if (str[index] != ' ' || index >= str.length()){
                    valid = false;
                    break;
                }
                string sy = str.substr(index + 1);
                double yy = stod(sy, &index);
                if (index != sy.length())
                    valid = false;
                if (valid)
                    input.insert({xx, yy});
            }
        }
        double x0 = input.begin()->first;
        double x1 = next(input.begin())->first;
        double h = x1 - x0;
        double tmp = x0;
        for (auto& kv : input){
            if ( kv == *input.begin()) continue;
            tmp += h;
            if (fabs(tmp - kv.first) < 1e-6) {}
            else {
                valid = false;
                break;
            }
        }
        if (!valid) {
            cout << "error" << endl;
            return 0;
        }

        vector<vector<double>> dif(input.size());
        vector<double> a;
        for (auto& kv : input){
            dif[0].push_back(kv.second); //save f(x) to dif [0];
        }
        a.push_back(dif[0][0]);
        double k_factorial = 1.0;
        double h_k = 1.0;
        for (int i = 1; i < input.size(); ++i){
            for (int j = 1; j < dif[i - 1].size(); ++j){
                dif[i].push_back(dif[i - 1][j] - dif[i - 1][j -1]); //Calculate delta^i y
            }
            k_factorial *= i;
            h_k *= h;
            a.push_back(dif[i][0]/ k_factorial / h_k);
        }
        double ans = 0;
        for (int i = 0; i < a.size(); ++i){
            double tmp = a[i];
            for (int j = 0; j <= i - 1; ++j){
                tmp = tmp * (x - (x0 + j * h));
            }
            ans = ans + tmp;
        }
        string anss = to_string(ans);
        int len = anss.length();
        anss.erase(len - 2);
        cout << anss << endl;

    
    } else{
   	//第二执行代码 完成 SimpleLinearRegression.cpp与 SimpleLinearRegression.h文件
    }
    
	/********** End **********/
    return 0;
}

