#include <bits/stdc++.h>
using namespace std;

template <typename T, auto Func = plus<>(), const bool idempotent = false>
class SparseTable {
public:
    vector<vector<T>> st;
    int k, n;
    template <typename Container>
    SparseTable(const Container& array) {
        k = 32 - __builtin_clz(unsigned(size(array)));
        n = 1 << k;
        st = vector(k + 1, vector<T>(n));
        copy(begin(array), end(array), begin(st[0]));
        for(int i = 1; i <= k; i++)
            for(int j = 0; j + (1 << i) <= n; j++)
                st[i][j] = Func(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);   
    }

    T query(int l, int r) {
        if constexpr (idempotent) {
            int i = bit_width((unsigned long)(r - l + 1)) - 1;
            return Func(st[i][l], st[i][r - (1 << i) + 1]);
        }else {
            T ans {};
            bool first = true;
            for(int i = k; i >= 0; i--) {
                if((1 << i) <= r - l + 1) {
                    if(first) {
                        ans = st[i][l], first = false;
                    }else {
                        ans = Func(ans, st[i][l]);
                    }
                    l += 1 << i;
                }
            }
            return ans;
        }
    }
};

const int K = 25, MAXN = 1e5;
int st[K + 1][MAXN];

int f(int a, int b) {
	return min(a, b);
}

void build(auto& array) {
	std::copy(array.begin(), array.end(), st[0]);

	for(int i = 1; i <= K; i++)
	    for(int j = 0; j + (1 << i) <= array.size(); j++)
	        st[i][j] = f(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
}

int query(int L, int R, int defaultVal = 0) {
	assert(L <= R);
	int ans = defaultVal;
	for(int i = K; i >= 0; i--) {
	    if((1 << i) <= R - L + 1) {
	        ans = f(ans, st[i][L]);
	        L += 1 << i;
	    }
	}
	return ans;
}
int query_idempotent(int L, int R) {
    int i = bit_width((unsigned)(R - L + 1)) - 1;
    return f(st[i][L], st[i][R - (1 << i) + 1]);
}