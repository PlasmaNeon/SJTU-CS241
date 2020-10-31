#include "std_lib_facilities.h"
#include "NodeRecognition.h"
//#include "TreeConstruct.h"
#include<vector>
#include<unordered_map>
#include<sstream>
#include<unordered_set>
#include<functional>

int main(){
    bool exercise_1=true;
    if(exercise_1){
        //第一关执行代码
        //Please fix NodeRecognition.h and NodeRecognition.cpp
        unordered_map<int, unordered_set<int>> g_; //  <from, to>
        unordered_map<int, unordered_set<int>> rg_; // <to, from>
        vector<int> roots;
        string s;
        getline(cin, s);
        int n = s.size();
        string buf;
        int i = 0;
        while (i < n){
            if (s[i] == '<'){
                ++i;
                while (s[i] != '>'){
                    buf += s[i];
                    ++i;
                }
                if (buf != "") { 
                    int pos = buf.find(' ');
                    if (pos != -1){
                        int to = stoi(buf.substr(0, pos));
                        int from = stoi(buf.substr(pos + 1));
                        g_[from].insert(to);
                        rg_[to].insert(from);
                        // Undirected graph
                    } else {
                        int root = stoi(buf);
                        roots.push_back(root);
                        if (!g_.count(root))
                            g_[root] = {};
                    }
                    buf = "";
                }
            }
            ++i;
        }

    
    vector<pair<int, int>> node_info;
    vector<pair<int, int>> btree_info;
    vector<pair<int, int>> tree_info;
    vector<pair<int, int>> graph_info;

    unordered_set<int> visited;
    if (g_.empty()){
        printTotal(0);
        return 0;
    }
    for (int r : roots){ // Check all root first
        if (visited.count(r)) continue;
        vector<int> res = checkHasRoot(g_, rg_, visited, r);
        int flag = res[0];
        if (flag == 1) 
            node_info.push_back({res[1], res[2]});
        else if (flag == 2) 
            btree_info.push_back({res[1], res[2]});
        else if (flag == 3) 
            tree_info.push_back({res[1], res[2]});
        else if (flag == 4) 
            graph_info.push_back({res[1], res[2]});
    }


    for (auto kv : g_){
        if (visited.count(kv.first)) continue;
        vector<int> res = checkNoRoot(g_, rg_, visited, kv.first);
        int flag = res[0];
        if (flag == 2) 
            btree_info.push_back({res[1], res[2]});
        else if (flag == 4) 
            graph_info.push_back({res[1], res[2]});
    }

    printTotal(node_info.size() + btree_info.size() + tree_info.size() + graph_info.size());
    auto comp = [](const pair<int, int>& a, const pair<int, int>& b){
        return ((a.first < b.first) || (a.first == b.first && a.second < b.second)); 
    };
    
    printInfo("Node", node_info);
    printInfo("Binary tree", btree_info);
    printInfo("Tree", tree_info);
    printInfo("Graph", graph_info);

    } else {
        //第二关执行代码
        //Please fix TreeConstruct.h and TreeConstruct.cpp


    }
	/********** End **********/
    return 0;
}

