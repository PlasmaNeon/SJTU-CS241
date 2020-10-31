#include "NodeRecognition.h"

void printTotal(int num){
    cout << "We have recognized " << num;
    if (num <= 1)
        cout << " graph." << endl;
    else cout << " graphs." << endl;
}

void printInfo(string gtype, vector<pair<int, int>>infos){
    auto comp = [](const pair<int, int>& a, const pair<int, int>& b){
        return ((a.first < b.first) || (a.first == b.first && a.second < b.second)); 
    };

    if (infos.size() > 1)
        sort(infos.begin(), infos.end(), comp);

    for (auto& p : infos){
        cout << "--" << gtype << ".";
        cout << " Weight: "<< p.first << ". Size: "<< p.second << "." << endl;
    }

}

// If root exists, check the type.
// Return val: [0]: node = 1, binary tree = 2, tree = 3, graph = 4;
//             [1]: weight: sum of all nodes' value.
//             [2]: size: number of nodes.
vector<int> checkHasRoot(unordered_map<int, unordered_set<int>>& g_, 
                        unordered_map<int, unordered_set<int>>& rg_, 
                        unordered_set<int>& visited, int root){
    if (g_[root].empty()) {
        visited.insert(root);
        return {1, root, 1};
    }

    queue<int> q;
    q.push(root);
    visited.insert(root);
    int max_to_deg = 0;
    int max_from_deg = 0;
    int flag = -1;
    int w = 0;
    int s = 0;
    while (!q.empty()){
        int size = q.size();
        s += size;
        while (size--){
            int f = q.front();
            q.pop();
            w += f;
            int to_deg = g_[f].size();
            int from_deg = rg_[f].size();
            max_to_deg = max(max_to_deg, to_deg);
            max_from_deg = max(max_from_deg, from_deg);

            for (int child : g_[f]){
                if (visited.count(child))
                    continue;
                q.push(child);
                visited.insert(child);
            }
            for (int parent : rg_[f]){
                if (visited.count(parent))
                    continue;
                q.push(parent);
                visited.insert(parent);
            }
        }
    }
    if (max_from_deg <= 1 && max_to_deg <= 2) flag = 2;
    else if (max_from_deg <= 1 && max_to_deg >= 3) flag = 3;
    else flag = 4;
    return {flag, w, s};
}

// If root does not exist, check the type.
// Return val: [0]: btree = 2, graph = 4.
//             [1]: weight: sum of all nodes' value.
//             [2]: size: number of nodes.
vector<int> checkNoRoot(unordered_map<int, unordered_set<int>>& g_, 
                        unordered_map<int, unordered_set<int>>& rg_, 
                        unordered_set<int>& visited, int root){
    queue<int> q;
    q.push(root);
    visited.insert(root);
    int max_to_deg = 0;
    int max_from_deg = 0;
    int flag = -1;
    int w = 0;
    int s = 0;

    while (!q.empty()){
        int size = q.size();
        s += size;
        while (size--){
            int f = q.front();
            q.pop();
            w += f;
            int to_deg = g_[f].size();
            int from_deg = rg_[f].size();
            max_to_deg = max(max_to_deg, to_deg);
            max_from_deg = max(max_from_deg, from_deg);
            for (int child : g_[f]){
                if (visited.count(child))
                    continue;
                q.push(child);
                visited.insert(child);
            }

            for (int parent : rg_[f]){
                if (visited.count(parent))
                    continue;
                q.push(parent);
                visited.insert(parent);
            }
        }
    }

    if (max_from_deg == 1 && max_to_deg == 1) {
        flag = 4; // circle
        return {flag, w, s};
    }

    if (max_from_deg <= 1 && max_to_deg <= 2) flag = 2;
    else if (max_from_deg <= 1 && max_to_deg >= 3) flag = 3;
    else flag = 4;

    return {flag, w, s};


}

