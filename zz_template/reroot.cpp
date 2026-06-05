#include <bits/stdc++.h>
using namespace std;


namespace reroot {
    const auto exclusive = [](const auto& a, const auto& base, const auto& merge_into, int vertex) {
        int n = (int)a.size();
        using Aggregate = std::decay_t<decltype(base)>;
        std::vector<Aggregate> b(n, base);
        for (int bit = (int)std::__lg(n); bit >= 0; --bit) {
            for (int i = n - 1; i >= 0; --i) b[i] = b[i >> 1];
            int sz = n - (n & !bit);
            for (int i = 0; i < sz; ++i) {
                int index = (i >> bit) ^ 1;
                b[index] = merge_into(b[index], a[i], vertex, i);
            }
        }
        return b;
    };
    // MergeInto : Aggregate * Value * Vertex(int) * EdgeIndex(int) -> Aggregate
    // Base : Vertex(int) -> Aggregate
    // FinalizeMerge : Aggregate * Vertex(int) * EdgeIndex(int) -> Value
    const auto rerooter = [](const auto& g, const auto& base, const auto& merge_into, const auto& finalize_merge) {
        int n = (int)g.size();
        using Aggregate = std::decay_t<decltype(base(0))>;
        using Value = std::decay_t<decltype(finalize_merge(base(0), 0, 0))>;
        std::vector<Value> root_dp(n), dp(n);
        std::vector<std::vector<Value>> edge_dp(n), redge_dp(n);
        
        std::vector<int> bfs, parent(n);
        bfs.reserve(n);
        bfs.push_back(0);
        for (int i = 0; i < n; ++i) {
            int u = bfs[i];
            for (auto v : g[u]) {
                if (parent[u] == v) continue;
                parent[v] = u;
                bfs.push_back(v);
            }
        }
        
        for (int i = n - 1; i >= 0; --i) {
            int u = bfs[i];
            int p_edge_index = -1;
            Aggregate aggregate = base(u);
            for (int edge_index = 0; edge_index < (int)g[u].size(); ++edge_index) {
                int v = g[u][edge_index];
                if (parent[u] == v) {
                    p_edge_index = edge_index;
                    continue;
                }
                aggregate = merge_into(aggregate, dp[v], u, edge_index);
            }
            dp[u] = finalize_merge(aggregate, u, p_edge_index);
        }
        
        for (auto u : bfs) {
            dp[parent[u]] = dp[u];
            edge_dp[u].reserve(g[u].size());
            for (auto v : g[u]) edge_dp[u].push_back(dp[v]);
            auto dp_exclusive = exclusive(edge_dp[u], base(u), merge_into, u);
            redge_dp[u].reserve(g[u].size());
            for (int i = 0; i < (int)dp_exclusive.size(); ++i) redge_dp[u].push_back(finalize_merge(dp_exclusive[i], u, i));
            root_dp[u] = finalize_merge(n > 1 ? merge_into(dp_exclusive[0], edge_dp[u][0], u, 0) : base(u), u, -1);
            for (int i = 0; i < (int)g[u].size(); ++i) {
                dp[g[u][i]] = redge_dp[u][i];
            }
        }
 
        return std::make_tuple(std::move(root_dp), std::move(edge_dp), std::move(redge_dp));
    };
}  // namespace reroot

void main_reroot(auto& adj) {

	using Aggregate = int;
    using Value = int;

    auto base = [&](int v) -> Aggregate {
    	return 0;
    };
    auto merge_into = [&](Aggregate vertex_dp, Value neighbor_dp, int vertex, int edge_index) -> Aggregate {
        return vertex_dp + neighbor_dp;
    };

    auto finalize_merge = [&](Aggregate vertex_dp, int vertex, int edge_index) -> Value {
        return vertex_dp;
    };

    auto [reroot_result, edge_dp, redge_dp] = reroot::rerooter(adj, base, merge_into, finalize_merge);

}

template <class Compute, class Result>
class Reroot {
public:
	vector<map<int, Result>> adj;
	vector<Compute> computeResult;
	vector<int> computeState;
	vector<bool> count;

	void add(Compute& c, Result childrenResult) {
		c.first += childrenResult.first + childrenResult.second;
		c.second += childrenResult.second;
	}

	void add_self(Compute& c, int u) {
		if(count[u]) {
			c.first++, c.second++;
		}
	}

	Result get_all(const Compute& c) {
		return c;
	}

	Result get_with_removed(const Compute& c, int u, int removed) {
		Result childrenResult = adj[u][removed];
		Result finalResult = c;

		finalResult.first += childrenResult.first + childrenResult.second;
		finalResult.second += childrenResult.second;

		return finalResult;
	}

	Result dfs(int u, int parent) {
		if(computeState[u] == INT_MAX) {
			for(auto& [v, result] : adj[u]) {
				if(v == parent) continue;
				result = dfs(v, u);
				add(computeResult[v], result);
			}
			add_self(computeResult[u], u);
			computeState[u] = parent;
		}else if(computeState[u] != -1 && computeState[u] != parent) {
			adj[u][computeState[u]] = dfs(computeState[u], u);
			add(computeResult[u], adj[u][computeState[u]]);
			computeState[u] = -1;
		}

		if(computeState[u] == -1 && parent != -1) {
			return get_with_removed(computeResult[u], u, parent);
		}else {
			return get_all(computeResult[u]);
		}
	}
};

int Reroot1() {

	// ex: sum(children)
	
	using Prop = int;
	using ReturnValue = int;
	auto add = [](Prop& target, ReturnValue rv) -> void {
		target += rv;
	};
	auto get_return_value = [](Prop& computed, ReturnValue removed, int vert) -> ReturnValue {
		return computed - removed;
	};
	
	// ex: min(children)
	/*
	using Prop = multiset<int>;
	using ReturnValue = int;

	auto add = [](Prop& target, ReturnValue rv) -> void {
		target.insert(rv);
		if(target.size() > 2) target.erase(prev(target.end()));
	};
	auto get_return_value = [](Prop& computed, ReturnValue removed, int vert) -> ReturnValue {
		if(*computed.begin() == removed) return *computed.rbegin();
		return *computed.begin();
	};
	*/


	int n;
	vector<map<int, ReturnValue>> adj;


	vector<Prop> computeResult(n);
	vector<int> computeState(n, INT_MAX);
	auto go = [&](this auto&& go, int v, int parent) -> ReturnValue {
		if(computeState[v] == INT_MAX) {
			for(auto& p : adj[v]) {
				if(p.first == parent) continue;
				p.second = go(p.first, v);
				add(computeResult[v], p.second);
			}
			computeState[v] = parent;
		}else if(computeState[v] != -1 && computeState[v] != parent) {
			adj[v][computeState[v]] = go(computeState[v], v);
			add(computeResult[v], adj[v][computeState[v]]);
			computeState[v] = -1;
		}
		return get_return_value(computeResult[v], (parent >= 0 ? adj[v][parent] : 0), parent);
	};
}

int Add() {
	// + between nodes
	int n;
	vector<map<int, int>> adj;
	vector<int> allCompute(n, 0);
	vector<int> computed(n, INT_MAX);
	auto go = [&](this auto&& go, int v, int prev) -> int {
		if(computed[v] == INT_MAX) {
			allCompute[v] = 0;
			for(auto& p : adj[v]) {
				if(p.first == prev) continue;
				p.second = go(p.first, v);
				allCompute[v] += p.second;
			}
			computed[v] = prev;
		}else if(computed[v] != -1 && computed[v] != prev) {
			int missingPiece = go(computed[v], v);
			adj[v][computed[v]] = missingPiece;

			allCompute[v] += missingPiece;
			computed[v] = -1;
		}
		return allCompute[v] - (prev >= 0 ? adj[v][prev] : 0);
	};
}

int MinOrMax() {
	// less<> for MAX, greater<> for MIN
	// because delete begin() sz > 2
	// currently max(children)
	using MS = multiset<pair<int, int>, less<>>;
	int n;
	vector<map<int, int>> adj;
	vector<MS> allCompute(n);
	vector<int> computed(n, INT_MAX);
	auto go = [&](this auto&& go, int v, int prev) -> int {
		if(computed[v] == INT_MAX) {
			for(auto& p : adj[v]) {
				if(p.first == prev) continue;
				p.second = go(p.first, v);


				allCompute[v].insert({p.second, p.first});
				if(allCompute[v].size() > 2) allCompute[v].erase(allCompute[v].begin());
			}

			computed[v] = prev;
			return allCompute[v].rbegin()->first;
		}else if(computed[v] != -1) {
			if(computed[v] == prev) return allCompute[v].rbegin()->first;

			int missingPiece = go(computed[v], v);
			adj[v][computed[v]] = missingPiece;

			allCompute[v].insert({missingPiece, computed[v]});
			if(allCompute[v].size() > 2) allCompute[v].erase(allCompute[v].begin());

			computed[v] = -1;
		}
		return (allCompute[v].rbegin()->second == prev) ? allCompute[v].begin()->first : allCompute[v].rbegin()->first;
	};
}


class Solution {
public:
    vector<int> timeTaken(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vector<map<int, int>> adj(n);
        for(auto& edge : edges) {
            adj[edge[0]][edge[1]] = adj[edge[1]][edge[0]] = 0;
        }

        vector<multiset<int>> computeResult(n);
        vector<int> computeState(n, INT_MIN);

        auto dfs = [&](this auto&& dfs, int v, int parent) -> int {
            if(computeState[v] == INT_MIN) {
                for(auto& p : adj[v]) {
                    if(p.first == parent) continue;
                    p.second = dfs(p.first, v);
                    computeResult[v].insert(p.second);
                    if(computeResult[v].size() > 2) computeResult[v].erase(computeResult[v].begin());
                }
                computeState[v] = parent;
            }else if(computeState[v] != -1 && computeState[v] != parent) {
                adj[v][computeState[v]] = dfs(computeState[v], v);
                computeResult[v].insert(adj[v][computeState[v]]);
                if(computeResult[v].size() > 2) computeResult[v].erase(computeResult[v].begin());

                computeState[v] = -1;
            }
            int ans = (parent == -1) ? 0 : (v % 2 == 1 ? 1 : 2);
            if(computeState[v] != parent && *computeResult[v].rbegin() == adj[v][parent]) {
                ans += (computeResult[v].size() != 1) * *computeResult[v].begin();
            }else if(!computeResult[v].empty()) {
                ans += *computeResult[v].rbegin();
            }
            return ans;
        };
        vector<int> res(n);
        for(int i = 0; i < n; i++) res[i] = dfs(i, -1);
        return res;
    }
};