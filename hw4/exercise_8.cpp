#include "std_lib_facilities.h"
//#include "Token_Exercise_1.h"
//#include "Code_Exercise_2.h"
#include<unordered_map>
int main()
{
    /********** Begin **********/
    
    bool exercise_1=true;
    if(exercise_1){
    //第一关执行代码
		//Please fix Token_Exercise_1.h and Token_Exercise_1.cpp
        string str;
        getline(cin,str);
        str += ' ';
        string sx;
        getline(cin, sx);
        sx += ' ';
        unordered_map<string, int> dict;

        int n = str.size();
        int i = 0;
        string buf;
        while (i < n){
            if (isalnum(str[i]) || str[i] == '_' || str[i] == '-'){
                if (isalnum(str[i]))
                    buf += tolower(str[i]);
                else if (str[i] == '-' || str[i] == '_')
                    buf += str[i];
            } else {
                //Process the buf
                if (buf.size() > 1 || buf.size() == 1 && isalnum(buf[0])){
                    //cout << buf << endl;
                    dict[buf]++;
                }
                buf = "";
            }
            i++;
        }
        n = sx.size();
        i = 0;
        buf = "";
        vector<int> ans;
        while (i < n){
            if (isalnum(sx[i]) || sx[i] == '_' || sx[i] == '-'){
                if (isalnum(sx[i]))
                    buf += tolower(sx[i]);
                else if (sx[i] == '-' || sx[i] == '_')
                    buf += sx[i];
            } else {
                cout << '(' << sx.substr(i - buf.size(), buf.size()) << ',' << dict[buf] << ')'<< ' ';
                buf = "";
            }
            i++;
        }
        cout << endl;
    
    
    }else{
    //第二关执行代码
    //Please fix Code_Exercise_2.h and Code_Exercise_2.cpp

    cout<<"error";
    }
	/********** End **********/
  	return 0;
}

