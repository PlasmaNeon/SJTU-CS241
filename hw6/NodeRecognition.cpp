#include "NodeRecognition.h"

void printTotal(int num){
    cout << "We have recognized " << num;
    if (num <= 1)
        cout << " graph." << endl;
    else cout << " graphs." << endl;
}

void printNode(int w, int s){
    cout << "--Node. Weight: "<< w << ". Size: "<< s << "." << endl;
}

void printBTree(int w, int s){
    cout << "--Binary tree. Weight: "<< w << ". Size: "<< s << "." << endl;
}

void printTree(int w, int s){
    cout << "--Tree. Weight: "<< w << ". Size: "<< s << "." << endl;
}

void printGraph(int w, int s){
    cout << "--Graph. Weight: "<< w << ". Size: "<< s << "." << endl;
}

// If root exists, check the type.
// Return val: [0]: node = 1, binary tree = 2, tree = 3, graph = 4;
//             [1]: weight: sum of all nodes' value.
//             [2]: size: number of nodes.
vector<int> checkHasRoot(unordered_map<int, unordered_set<int>>& g_, unordered_set<int>& visited, int root){
    if (g_[root].empty()) {
        visited.insert(root);
        return {1, root, 1};
    }

    queue<int> q;
    q.push(root);
    visited.insert(root);
    int max_size = 0;
    int flag = -1;
    int w = 0;
    int s = 0;
    while (!q.empty()){
        int size = q.size();
        s += size;
        max_size = max(max_size, size);
        while (size--){
            int f = q.front();
            q.pop();
            visited.insert(f);
            w += f;
            if (g_.count(f)){
                for (int num : g_[f]){
                    if (visited.count(num)){
                        flag = 4;
                        continue;
                    }
                    q.push(num);
                }
            }
        }
    }
    if (max_size <= 2) flag = 2;
    else flag = 3;
    return {flag, w, s};
}

// If root does not exist, check the type.
// Return val: [0]: btree = 2, graph = 4.
//             [1]: weight: sum of all nodes' value.
//             [2]: size: number of nodes.
vector<int> checkNoRoot(unordered_map<int, unordered_set<int>>& g_, unordered_set<int>& visited, int root){
    queue<int> q;
    q.push(root);
    visited.insert(root);
    int max_size = 0;
    int flag = -1;
    int w = 0;
    int s = 0;

    while (!q.empty()){
        int size = q.size();
        s += size;
        max_size = max(max_size, size);
        while (size--){
            int f = q.front();
            q.pop();
            w += f;
            if (g_.count(f)){
                for (int num : g_[f]){
                    if (!visited.count(num)){
                        q.push(num);
                        visited.insert(num);
                    }
                }
            }
        }
    }

    if (max_size == 1){
        flag = 2;
    } else flag = 4;

    return {flag, w, s};


}