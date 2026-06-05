#include <bits/stdc++.h>
using namespace std;

struct Query {
	int l, r, idx;
	int64_t key;
};

inline int64_t hilbertOrder(int x, int y) {
	constexpr uint64_t logn = 18;
    constexpr uint64_t maxn = (1ull << logn) - 1;
    uint64_t res = 0;
    for (uint64_t s = 1ull << (logn - 1); s; s >>= 1) {
        bool rx = x & s, ry = y & s;
        res = (res << 2) | (rx ? ry ? 2 : 1 : ry ? 3 : 0);
        if (!rx) {
            if (ry) x ^= maxn, y ^= maxn;
            swap(x, y);
        }
    }
    return res;
}

template <typename R>
vector<R> mo_algorithm(int n, vector<Query>& queries, auto& add_idx, auto& remove_idx, auto& get_answer) {
	for(Query& query : queries) {
		query.key = hilbertOrder(query.l, query.r);
	}

	sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) -> bool {
		return a.key < b.key;
	});

	vector<R> answers(q);
	int l = 0, r = -1;
	for(Query& query : queries) {
		while(l > query.l) {
            l--;
            add_idx(l);
        }
        while(r < query.r) {
            r++;
            add_idx(r);
        }
        while(l < query.l) {
            remove_idx(l);
            l++;
        }
        while(r > query.r) {
            remove_idx(r);
            r--;
        }
        answers[query.idx] = get_answer(query);
	}
	return answers;
}