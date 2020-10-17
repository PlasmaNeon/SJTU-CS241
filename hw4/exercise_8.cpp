    #include "std_lib_facilities.h"
    //#include "Token_Exercise_1.h"
    //#include "Code_Exercise_2.h"
    #include<unordered_map>
    #include<unordered_set>
    #include<set>
    #include<functional>
    int main()
    {
        /********** Begin **********/
        
        bool exercise_1= false;
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
            unordered_set<string> kwds = {"alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept",
                                            "auto", "bitand", "bitor", "bool", "break", "case", "catch", "char",
                                            "char8_t", "char16_t", "char32_t", "class", "compl", "concept", "const", "consteval",
                                            "constexpr", "constinit", "const_cast", "continue", "co_await", "co_return", "co_yield", "decltype", 
                                            "default", "define", "defined", "delete", "do", "double", "dynamic_cast", "elif", 
                                            "else", "error", "endif", "enum", "explicit", "export", "extern", "false",
                                            "final", "float", "for", "friend", "goto", "if", "ifdef", "ifndef",
                                            "import", "include", "inline", "int", "line", "long", "module", "mutable", 
                                            "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or",
                                            "or_eq", "override", "pragma", "private", "protected", "public", "reflexpr", "register",
                                            "reinterpret_cast", "requires","return", "short signed", "sizeof", "static", "static_assert",
                                            "static_cast", "struct", "switch", "synchronized template", "this", "thread_local", "throw",
                                            "xor_eq", "true", "try", "typedef", "typeid", "typename", "undef", "union",
                                            "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor"};
            

            string s1, s2;
            vector<string> input;
            set<string> ans;
            bool incomment = false;
            int instring = 0;
            function<void(string)> process = [&](string s){ 
                    s+= ' ';
                    string buf;
                    int n = s.size();
                    int i = 0;
                    
                    while (i < n){
                        if (isalnum(s[i]) || s[i] == '_'){
                            buf += s[i];
                        } 
                        else if (i + 1 < n && s[i] == '/' && s[i + 1] == '/') {
                            // Meet '//' comments.
                            break;
                        }
                        else if (i + 1 < n && s[i] =='/' && s[i + 1] == '*'){
                            // Meet /* */ comments
                            incomment = true;
                        }
                        else if (i + 1 < n && s[i] == '*' && s[i + 1] == '/'){
                            incomment = false;
                            buf = "";
                        }
                        else if (i + 1 < n && s[i] == '\\' && s[i + 1] == 'n' ){
                            buf+=s[i];
                        }
                        else {
                            // Meet blank, process buf.
                            if (!kwds.count(buf) && !isdigit(buf[0]) && !incomment && !instring)
                                ans.insert(buf);
                            buf = "";
                        }
                        i++;
                    }
                };
            
            while (getline(cin, s1) ){
                //if (s1.size() ==0) break;
                process(s1);
            }
            //sort(ans.begin(), ans.end(), less<string>());
            for (string si : ans){
                if (si == "\\n" || si ==" \\n") continue;
                if (si.size())
                    cout << si << ' ';
            }
            cout << endl;
        }
        /********** End **********/
        return 0;
    }

