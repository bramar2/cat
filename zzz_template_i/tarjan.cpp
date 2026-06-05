#include <bits/stdc++.h>
using namespace std;

// get all Strongly Connected Components (SCC) where you can reach every node from every other node in a Directed Graph
// https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm#The_algorithm_in_pseudocode
vector<vector<int>> tarjan(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<vector<int>> res;

    int index = 0;
    vector<int> S;

    vector<int> v_index(n, -1), v_lowlink(n, -1);
    vector<bool> v_onStack(n);

    auto strongconnect = [&](auto&& self, int v) -> void {
        v_index[v] = v_lowlink[v] = index;
        index++;
        S.push_back(v);
        v_onStack[v] = true;

        for(int w : adj[v]) {
            if(v_index[w] == -1) {
                self(self, w);
                v_lowlink[v] = min(v_lowlink[v], v_lowlink[w]);
            }else if(v_onStack[w]) {
                v_lowlink[v] = min(v_lowlink[v], v_index[w]);
            }
        }

        if(v_lowlink[v] == v_index[v]) {
            res.emplace_back();
            int w;
            do {
                w = S.back();
                S.pop_back();
                v_onStack[w] = false;
                res.back().push_back(w);
            }while(w != v);
        }
    };

    for(int v = 0; v < n; v++) {
        if(v_index[v] == -1) {
            strongconnect(strongconnect, v);
        }
    }
    return res;
}