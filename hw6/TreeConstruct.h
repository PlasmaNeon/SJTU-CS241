#include "std_lib_facilities.h"
#include<unordered_map>
#include<unordered_set>
#include<queue>

typedef unordered_map<char, unordered_set<char>> Graph;

char processInput(const string& s, 
                    Graph& g_, Graph& rg_);

int checkTree(Graph& g_, Graph& rg_, char& root);
string constructAHU(Graph& g_, char root);