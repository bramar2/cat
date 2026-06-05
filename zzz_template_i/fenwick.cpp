#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct FenwickTree {
	int sz;
	vector<T> bit;

	explicit FenwickTree(int c_sz) : sz(c_sz + 1), bit(c_sz + 1) {}

	T query(int r) {
		T ans {};
		for(r++; r > 0; r -= r & -r)
			ans += bit[r];
		return ans;
	}
	T query(int l, int r) {
		assert(l <= r);
		return query(r) - query(l - 1);
	}
	void update(int i, T delta) {
		for(i++; i < sz; i += i & -i)
			bit[i] += delta;
	}
	void clear() {
		fill(bit.begin(), bit.end(), T{});
	}
};