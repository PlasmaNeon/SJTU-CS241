#include "std_lib_facilities.h"
#include<unordered_map>
#include<vector>
#include<queue>
#include<unordered_set>

using namespace std;

void printTotal(int num);

void printNode(int w, int s);

void printBTree(int w, int s);

void printTree(int w, int s);

void printGraph(int w, int s);

vector<int> checkHasRoot(unordered_map<int, unordered_set<int>>& g_, unordered_set<int>& visited, 
                            int root);

vector<int> checkNoRoot(unordered_map<int, unordered_set<int>>& g_, unordered_set<int>& visited, int root);