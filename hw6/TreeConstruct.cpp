#include "TreeConstruct.h"

// Process input string.
// Input: string to be done.
// Output: Graph g_, reversed graph rg_
// Return val: root if exists, ' ' if not.

char processInput(const string& s, //input
                    Graph& g_, Graph& rg_  //output
                    ){
    int n = s.size();
    string buf;
    int i = 0;
    char root = ' ';
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
                    char to = buf[0];
                    char from = buf[2];
                    g_[from].insert(to);
                    rg_[to].insert(from);
                } else {
                    root = buf[0];
                    if (!g_.count(root))
                        g_[root] = {};
                }
                buf = "";
            }
        }
        ++i;
    }
    return root;
}

// Return val: depth
int checkTree(Graph& g_, Graph& rg_, char& root){
    if (g_.empty()) return 0;
    queue<char> q;
    unordered_set<char> visited;
    if (root != ' ')
        q.push(root);
    else q.push(g_.begin()->first);
    visited.insert(q.front());

    int depth = 1;
    while (!q.empty()){
        int size = q.size();
        ++depth;
        while (size--){
            char f = q.front();
            q.pop();
            int to_deg = g_[f].size();
            int from_deg = rg_[f].size();
            if (from_deg == 0) 
                root = f;
            for (char child : g_[f]){
                if (visited.count(child))
                    continue;
                q.push(child);
                visited.insert(child);
            }

            for (char parent : rg_[f]){
                if (visited.count(parent))
                    continue;
                q.push(parent);
                visited.insert(parent);
            }
        }
    }
    return depth;
}

string constructAHU(Graph& g_, char root){
    if (g_[root].size() == 0) return "10";
    string s = "1";
    vector<string> child_codes;
    for (char child : g_[root]){
        child_codes.push_back(constructAHU(g_, child));
    }
    sort(child_codes.begin(), child_codes.end(), greater<string>());
    for (string code : child_codes)
        s += code;
    s += "0";
    return s;
}