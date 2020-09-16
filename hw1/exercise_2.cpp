#include "std_lib_facilities.h"
#include "Polynomial.h"

int main()
{
    //请打开文件目录修改Polynomial.h，Polynomial.cpp，和exercise_2.cpp
    /********** Begin **********/
    bool exercise1 = false;
    if (exercise1){
        //第一关执行代码
        string str;          
        getline(cin,str);
        double x;
        cin >> x;
        Polynomial poly(str);
        poly.printPolynomial();
        poly.printDerivation();
        poly.printValueAtX(x);
    } else {
    //第二关执行代码
        string diviend_s, divisor_s;
        getline(cin, diviend_s);
        getline(cin, divisor_s);
        Polynomial diviend(diviend_s);
        Polynomial divisor(divisor_s);
        map<int, float> res;
        map<int, float> remain;
        //diviend.printPolynomial();
        //divisor.printPolynomial();
        div(diviend, divisor, res, remain);
        //cout<<"res = ";
        printMap(res);
        //cout << "remain =";
        printMap(remain);
    }
	/********** End **********/
  	return 0;
}

