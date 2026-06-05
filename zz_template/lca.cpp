#include <bits/stdc++.h>
using namespace std;

int main() {
    // provide these
    int n;
    vector<vector<int>> adj;

    //


    int timer;
    vector<int> tin, tout;
    vector<vector<int>> up;
    int l = ceil(log2(n));
    {
        tin.resize(n);
        tout.resize(n);
        timer = 0;
        up.assign(n, vector<int>(l + 1));
        auto dfs = [&](auto&& dfs, int v, int p) -> void {
            tin[v] = ++timer;
            up[v][0] = p;
            for (int i = 1; i <= l; ++i)
                up[v][i] = up[up[v][i-1]][i-1];

            for (int u : adj[v]) {
                if (u != p)
                    dfs(dfs, u, v);
            }

            tout[v] = ++timer;
        };
        dfs(dfs, 0, 0);
    }
    auto is_ancestor = [&](int u, int v) -> bool {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    };
    auto lca = [&](int u, int v) -> int {
        if (is_ancestor(u, v))
            return u;
        if (is_ancestor(v, u))
            return v;
        for (int i = l; i >= 0; --i) {
            if (!is_ancestor(up[u][i], v))
                u = up[u][i];
        }
        return up[u][0];
    };

    vector<int> depth(n);

    auto dfs_depth = [&](auto&& self, int u, int parent, int d) -> void {
        depth[u] = d;
        for(int v : adj[u]) {
            if(v != parent) {
                self(self, v, u, d + 1);
            }
        }
    };
    dfs_depth(dfs_depth, 0, -1, 0);

    auto shortest = [&](int u, int v) -> int {
        if(u == v) return 0;
        int ancestor = lca(u, v);
        if(ancestor == u) return depth[v] - depth[u];
        if(ancestor == v) return depth[u] - depth[v];

        return depth[u] + depth[v] - 2 * depth[ancestor];
    };
}