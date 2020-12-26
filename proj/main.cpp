#include "helper.h"

vector<DiGraph> ans;
set<vector<int>> deleted_edges;

void usage(){
    cout << "Usage: " << endl;
    cout << "Type a char to select a option, then input parameters. "<< endl;
    cout << "Options: " << endl;
    cout << "i      Input a txt file and load it." << endl;
    cout << "s      Save a graph to a file." << endl;
    cout << "a      Append another graph file into current graph." << endl;
    cout << "g      Generate a random graph." << endl;
    cout << "c      Set a limit of node numbers in each sub-graph and cut the graph using min-cut algorithm." << endl;
    cout << "d      Calculate min distance from a start node to an end node. If cannot reach, print -1" << endl;
    cout << "r      Search all reachable nodes given a start node." << endl;
    cout << "z      Restore all the sub-graphs into original graph and check if they are the same" << endl;
    cout << "h      Help info, print this message." << endl;
    cout << "q      Quit." << endl;
}

void eval(string file_name, DiGraph& dg){
    ifstream ifs(file_name);
    string s;
    int start, end, weight;
    while (getline(ifs, s)){
        start = end = weight = -1;
        s = s.substr(1);
        s.pop_back();
        istringstream ss(s);
        string sstart, send, sw;
        getline(ss, sstart, ',');
        getline(ss, send, ',');
        getline(ss, sw);
        start = (sstart.size() ? stoi(sstart) : -1);
        end = (send.size() ? stoi(send) : -1);
        weight = (sw.size() ? stoi(sw) : -1);
        //if (ss >> start >> end >> weight){
            if (start == -1) continue;
            dg.nodes.insert(start);
            if (end == -1) {
                continue;
            }
            dg.nodes.insert(end);
            if (weight == -1) weight = 1;
            if (dg.edges[start][end])
                cout << "Duplicate insert, overwrite it." << endl;
            dg.edges[start][end] = weight;
        //}
    }
    cout << "The graph has " << dg.nodes.size() << " nodes." << endl;
    ifs.close();
}

void save(string file_name, DiGraph& dg){
    ofstream ofs(file_name);
    for (auto& node : dg.nodes) {
        if (!dg.edges.count(node)) ofs << '<' << node << '>' << endl;
        else {
            for (auto&[d, w] : dg.edges[node])
                ofs << '<' << node << ',' << d << ',' << w << '>' << endl;
        }
    }
    cout << "Succeed to save the graph into " << file_name << endl;
    ofs.close();
}

void saveCutResult(string file_name_prefix){
    /*cout << "Input save filename prefix: ";
    string s;
    cin >> s;*/
    for (int i = 0; i < ans.size(); ++i) {
        //cout << ans[i].nodes.size() << endl;
        save(file_name_prefix + '_' + to_string(i) + ".txt", ans[i]);
    }

    ofstream ofs(file_name_prefix + "_deleted.txt");
    for (auto& d : deleted_edges)
        ofs << d[0] << ' ' << d[1] << ' ' << d[2] << endl;
    ofs.close();
}

void generateRandomGraph(DiGraph& dg){
    int n, e, node_l, node_r, weight_l, weight_r;
    cout << "Input number of nodes to be generated, node values will be in [0, n - 1]: ";
    cin >> n;
    for (int i = 0; i < n; ++i)
        dg.nodes.insert(i);
    cout << "Input the weight range between two connected nodes: ";
    cin >> weight_l >> weight_r;
    default_random_engine generator;
    uniform_int_distribution<int> dest_prob(0, n);
    uniform_int_distribution<int> weight_val(weight_l, weight_r);
    for (int i = 0; i < n; ++i){ //Traverse every node as src
        int src = i;
        while (dg.edges[src].size() == 0){ // Ensure that at least one edge is generated.
            for (int j = 0; j < n; ++j){  // Traverse other nodes
                if (i == j) continue;   // Ensure no self loop
                int prob = dest_prob(generator);  // uniformly distributed chance to connect two nodes.
                if (prob == j){
                    for (auto& dw : dg.edges[src]){
                        if (dw.first == j) continue;  //  Ensure no duplicate edges
                    }
                    int w = weight_val(generator);
                    dg.edges[src][j] = w;  //Generate
                }
            }
        }
    }

}

void appendToGraph(string& file_name, DiGraph& dg){
    eval(file_name, dg);
    return;
}

void cutGraph(DiGraph& dg, int max_nodes){
    if (dg.nodes.size() <= max_nodes) {
        ans.push_back(dg);
    }
    else {
        pair<DiGraph, DiGraph> sub;
        sub = minCut(dg);
        cutGraph(sub.first, max_nodes);
        cutGraph(sub.second, max_nodes);
    }
}

vector<int> getReachableNodes(DiGraph& dg, int start){
    vector<int> ans;
    queue<int> q;
    if (!checkValidNode(dg, start))
        error("The input node is not in the graph.");
    q.push(start);
    while (!q.empty()){
        int size = q.size();
        while (size--){
            int f = q.front();
            q.pop();
            ans.emplace_back(f);
            for (auto [d, w] : dg.edges[f])
                q.push(d);
        }
    }
    for (int a : ans){
        cout << a << ' ';
    }
    cout << endl;
    return ans;
}

int getMinDistance(DiGraph& dg, int start, int end){
    //Dijkstra
    if (!checkValidNode(dg, start) && !checkValidNode(dg, end))
        error("The input node is not in the graph.");
    unordered_map<int, int> dist;
    for (int no : dg.nodes)
        dist[no] = INT_MAX;
    dist[start] = 0;

    unordered_set<int> visited;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; //{min distance, cur node}
    pq.push({0, start});
    while (!pq.empty()){
        auto t = pq.top();
        pq.pop();
        if (visited.count(t.second)) continue;
        visited.insert(t.second);
        for (auto& [d, w] : dg.edges[t.second]){
            if (dist[t.second] + w < dist[d] ){
                dist[d] = dist[t.second] + w;
                pq.push({dist[d], d });
            }
        }
    }

    if (dist[end] == INT_MAX) {
        cout << -1 << endl;
        return -1;
    }
    else {
        cout << dist[end] << endl;
        return dist[end];
    }


}

bool checkValidNode(DiGraph& dg, int node){
    if (!dg.nodes.count(node)) return false;
    return true;
}

pair<DiGraph, DiGraph> minCut(DiGraph& dg){
    vector<pair<int, int>> contractions;
    unordered_set<int> A; // Pick an arbitary node and create a set A = {u}
    int cut_val = INT_MAX;
    int best_phase = 0;
    unordered_set<int> nodes = dg.nodes;

    auto comp = [](pair<int, int> a, pair<int, int> b){
        return a.second > b.second;
    };
    std::multiset<pair<int, int>, decltype(comp)> h(comp);

    unordered_map<int, unordered_map<int, int>> G;
    //Undirected graph G[i][j] = G[j][i] = weight
    // src : {dest : weight}

    for (auto [src, dst] : dg.edges){
        for (auto [d, e]: dst){
            G[src][d] += e;
            G[d][src] += e;
        }
    }
    int n = G.size();

    // Stoer-Wagner Min-Cut Algorithm
    unordered_set<int> seen = nodes;
    int u, v, w;
    for (int i = 0; i < n - 1; ++i){  // Go n - 1 rounds to pick the best
        auto rand_it = next(begin(seen), rand() % seen.size());
        u = *min_element(nodes.begin(), nodes.end());
        A.clear();
        A.insert(u);
        h.clear();
        // max heap, save {another node, weight sum to A}
        // h.begin() is the max weight value
        for (auto [v, e] : G[u]) {
            h.insert({v, e});
        }

        for (int j = 0; j < n - i - 2; ++j){
            u = h.begin()->first;
            A.insert(u);
            //if (!h.empty())
            h.erase(h.begin());

            for (auto [v, e] : G[u]){
                if (!A.count(v)){ // if v not in A
                    auto it_v = h.begin();
                    for (; it_v != h.end(); it_v++)
                        if (it_v->first == v) break;

                    if (it_v != h.end()) {
                        pair<int, int> tmp = *it_v;
                        tmp.second += e;
                        h.erase(it_v);
                        h.insert(tmp);
                    }
                    else h.insert({v, e});
                }
            }
        }

        v = h.begin()->first;
        w = h.begin()->second;
        if (w < cut_val){
            cut_val = w;
            best_phase = i;
        }
        contractions.emplace_back(u, v);
        for (auto [w, e] : G[v]){
            if (w != u){
                if (!G[u].count(w)){
                    G[u][w] = e;
                    G[w][u] = e;
                } else {
                    G[u][w] += e;
                    G[w][u] += e;
                }
            }
        }
        // Remove node v
        G.erase(v);
        for (auto& de : G){
            de.second.erase(v);
        }
        seen.erase(v);
    }

    /*for (int i = 0; i < contractions.size(); ++i)
        cout << contractions[i].first <<' ' << contractions[i].second << endl;
    cout << best_phase << endl;*/

    unordered_set<int> best;
    for (int i = 0; i < best_phase; ++i) {
        best.insert(contractions[i].first);
        best.insert(contractions[i].second);
    }


    unordered_map<int, unordered_map<int, int>> best_g;
    for (auto [s, dw] : dg.edges){
        if (!best.count(s)) continue;
        for (auto& [d, w] : dw){
            if (!best.count(d)) continue;
            best_g[s][d] = w;
            best_g[d][s] = w;
        }
    }
    v = contractions[best_phase].second;

    unordered_set<int> reachable;

    auto getAllReachableNodes = [&](int node){
        queue<int> q;
        unordered_set<int> ans;
        q.push(node);
        while (!q.empty()){
            int size = q.size();
            while (size--){
                int f = q.front();
                q.pop();
                ans.insert(f);
                for (auto& [d, w] : best_g[f]){
                    if (ans.count(d)) continue;
                    q.push(d);
                }

            }
        }
        return ans;
    };

    reachable = getAllReachableNodes(v);
    unordered_set<int> other;
    for (auto nn : nodes){
        if (reachable.count(nn)) continue;
        other.insert(nn);
    }

    /*for (auto i : reachable)
        cout << i << ' ';
    cout << endl;
    for (auto i : other)
        cout << i << ' ';*/

    DiGraph a;
    DiGraph b;
    a.nodes = reachable;
    for (auto& [s, dw] : dg.edges){
        if (!a.nodes.count(s)) continue;
        for (auto& [d, w] : dw){
            if (!a.nodes.count(d)) {
                deleted_edges.insert({s, d, w});
                continue;
            }
            a.edges[s][d] = w;
        }
    }

    b.nodes = other;
    for (auto& [s, dw] : dg.edges){
        if (!b.nodes.count(s)) continue;
        for (auto& [d, w] : dw){
            if (!b.nodes.count(d)) {
                deleted_edges.insert({s, d, w});
                continue;
            }
            b.edges[s][d] = w;
        }
    }
    return {a, b};
}

void restoreAndCheck(DiGraph& dg){
    DiGraph cur;
    for (auto& a : ans){
        for (auto& [s, dw] : a.edges)
            for (auto& [d, w] : dw)
                cur.edges[s][d] = w;
        for (auto& no : a.nodes)
            cur.nodes.insert(no);
    }
    for (auto& d : deleted_edges){
        cur.edges[d[0]][d[1]] = d[2];
        cur.nodes.insert(d[0]);
        cur.nodes.insert(d[1]);
    }
    if (cur.nodes == dg.nodes && cur.edges == dg.edges) cout << "Valid check!" << endl;

}

int main(int argc, char **argv){
    /* code */
    char c;
    DiGraph dg;
    MODE flag;
    bool graph_imported_flag;
    //usage();
    string fname;
    string sname;
    string aname;
    while (1){
        cout << "> ";
        cin >> c;
        switch (c){
            case 's':
                cout << "Input save file name: ";
                cin >> sname;
                save(sname, dg);
                break;
            case 'g':
                generateRandomGraph(dg);
                break;
            case 'q':
                return 0;
            case 'h':
                usage();
                break;
            case 'i':
                cout << "Input graph filename: ";
                cin >> fname;
                eval(fname, dg);
                graph_imported_flag = true;
                break;
            case 'a':
                cout << "Input filename to be appended: ";
                cin >> aname;
                appendToGraph(aname, dg);
                break;
            case 'c':
                if (!graph_imported_flag)
                    cout << "You have not input a graph!" << endl;
                else {
                    int max_node;
                    cout << "Input max nodes in a sub-graph: ";
                    cin >> max_node;
                    cutGraph(dg, max_node);
                    cout << "Done." << endl;
                    saveCutResult(fname);
                }
                break;
            case 'd':
                int start, end;
                cout << "Input start node and end node: ";
                cin >> start >> end;
                getMinDistance(dg, start, end);
                break;
            case 'r':
                int st;
                cout << "Input a start node: ";
                cin >> st;
                getReachableNodes(dg, st);
                break;
            case 'z':
                restoreAndCheck(dg);
                break;
            default:
                usage();
                break;
        }
    }


    //eval("../infile3.txt", dg);
    //minCutTmp(dg);
    /*cutGraph(dg, 5);
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i].nodes.size() << endl;
        save("out_" + to_string(i) + ".txt", ans[i]);
    }*/
    return 0;
}
