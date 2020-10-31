#include "std_lib_facilities.h"
#include<unordered_map>
#include<vector>
#include<queue>
#include<unordered_set>
#include<functional>
using namespace std;

void printTotal(int num);

void printInfo(string, vector<pair<int, int>>);

vector<int> checkHasRoot(unordered_map<int, unordered_set<int>>& g_, 
                        unordered_map<int, unordered_set<int>>& rg_, 
                        unordered_set<int>& visited, int root);

vector<int> checkNoRoot(unordered_map<int, unordered_set<int>>& g_, 
                        unordered_map<int, unordered_set<int>>& rg_, 
                        unordered_set<int>& visited, int root);