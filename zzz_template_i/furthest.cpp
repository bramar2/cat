#include <bits/stdc++.h>
using namespace std;

array<int, 2> furthest(auto& adj, int start = 0) {
    int ans = start, ans_dist = 0;

    [&](this auto&& dfs, int u, int d = 0, int p = -1) -> void {
        if(d > ans_dist) ans = u, ans_dist = d;

        for(int v : adj[u]) if(v != p)
            dfs(v, d + 1, u);
    }(start);

    return {ans, ans_dist};
}