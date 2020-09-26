#include "std_lib_facilities.h"
#include "Polynomial.h"
#include "LinearEquations.h"

int main()
{
    /********** Begin **********/
    
    bool exercise1 = true;
    if(!exercise1){
      //第一关执行代码
      //Please fix Polynomial.h and Polynomial.cpp
      string str;          
      getline(cin,str);
      float l, r;
      cin >> l >> r;
      Polynomial p(str);
      if (!p.isvalid || !ensureSecondDerivativeExists(p) || l >=r )
          cout<<"error" << endl ;
      else{
          p.der = calcDerivation(p.saved);
          p.der2 = calcDerivation(p.der);
          float ans;
          if (newton(p, l, r, ans)){
            printFloat4c(ans);
          }
          else{
            cout << "error" << endl;
          }
      }
    } else {
    //第二关执行代码
    //Please fix LinearEquations.h and LinearEquations.cpp
        LinearEquations eqs;
        if (!eqs.isvalid)
          cout << "error" << endl;
        else {
          //printEqs(eqs);
          //printRight(eqs);
          map<int, double> ans;
          if (gauss(eqs, ans)){
            //cout << "success" << endl;
            printAns(ans);
          } else {
            cout << "gauss error" << endl;
          }
        }
    }
	/********** End **********/
  return 0;
}




