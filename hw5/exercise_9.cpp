#include "std_lib_facilities.h"
//#include "Huffman_Exercise_1.h"
//#include "Huffman_Exercise_2.h"
#include<vector>
#include<functional>
#include<queue>
#include<unordered_map>
int main()
{
    /********** Begin **********/
    bool exercise_1 = false;
    if (exercise_1){
        //第一关执行代码
        //Please fix Huffman_Exercise_1.h and Huffman_Exercise_1.cpp
        vector<int> freq(128,0);
        vector<int> codelen(128, 0);
        
        auto comp = [](pair<string, int>& a, pair<string, int>& b){
            return (a.second > b.second || ( a.second == b.second && a.first > b.first));
        };
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(comp)> pq(comp);
        
        char c;

        while (c = getchar()){
            if (c == EOF) break;
            freq[c]++;
        }
        
        for (int i = 0; i < freq.size(); ++i){
            if (freq[i])
                pq.push({string(1, i), freq[i]});
        }

        if (pq.size() == 1){
            pair<string, int> a = pq.top();
            codelen[a.first[0]]++;
        }

        while(pq.size() > 1){
            pair<string, int> a = pq.top();
            pq.pop();
            pair<string, int> b = pq.top();
            pq.pop();
            for (char c : a.first)
                codelen[c]++;
            for (char c : b.first)
                codelen[c]++;
            pq.push({a.first + b.first, a.second + b.second});
        }

        int ans = 0;
        for (int i = 0; i < 128; i++){
            ans += freq[i] * codelen[i];
        }

        cout << ans << endl;
        


    } else {
        //Please fix Huffman_Exercise_2.h and Huffman_Exercise_2.cpp  
        unordered_map<string, int> freqs;
        unordered_map<string, int> codelen;
        int split_num = 0;
        char c;
        string buf;
        while (c = getchar()){
            if (c == EOF) break;
            if (isalpha(c))
                buf += c;
            else {
                split_num++;
                if (buf.size())
                    freqs[buf]++;
                buf = "";
            }
        }
        if (buf.size()) freqs[buf]++;

        auto comp = [](pair<vector<string>, int>& a, pair<vector<string>, int>& b){
            return (a.second > b.second);
        };
        priority_queue<pair<vector<string>, int>, vector<pair<vector<string>, int>>, decltype(comp)> pq(comp);

        for (auto& f : freqs){
            vector<string> vs{f.first};
            pq.push({vs, f.second});
        }

        if (pq.size() == 1){
            pair<vector<string>, int> t = pq.top();
            codelen[t.first[0]]++;
        }

        while (pq.size() > 1){
            pair<vector<string>, int> a = pq.top();
            pq.pop();
            pair<vector<string>, int> b = pq.top();
            pq.pop();
            vector<string> vs;
            for (string& str : a.first){
                codelen[str]++;
                vs.push_back(str);
            }
            for (string& str : b.first){
                codelen[str]++;
                vs.push_back(str);
            }
            pq.push({vs, a.second + b.second});
        }

        int ans = 0;
        for (auto& kv : freqs){
            ans += kv.second * codelen[kv.first];
        }
        //cout << ans << endl;
        cout << ans + split_num * 8<< endl;
    }
    /********** End **********/
    return 0;
}

