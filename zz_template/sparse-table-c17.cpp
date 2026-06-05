#include <bits/stdc++.h>
using namespace std;

template <class T>
struct c_merge {
    T operator() (T a, T b) {
        return a + b;
    }
};

template <typename T, class Func = plus<T>, const bool idempotent = false>
class SparseTable {
public:
    vector<vector<T>> st;
    int k, n;
    template <typename Container>
    SparseTable(const Container& array) {
        assert(size(array) > 0);
        n = unsigned(size(array));
        k = 31 - __builtin_clz(n);
        st = vector(k + 1, vector<T>(n));
        copy(begin(array), end(array), begin(st[0]));
        for(int i = 1; i <= k; i++)
            for(int j = 0; j + (1 << i) <= n; j++)
                st[i][j] = Func()(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);   
    }

    T query(int l, int r) {
        if constexpr (idempotent) {
            unsigned long long len = r - l + 1;
            int i = len ? __builtin_clzll(1) - __builtin_clzll(len) : -1;
            return Func()(st[i][l], st[i][r - (1 << i) + 1]);
        }else {
            T ans {};
            bool first = true;
            for(int i = k; i >= 0; i--) {
                if((1 << i) <= r - l + 1) {
                    if(first) {
                        ans = st[i][l], first = false;
                    }else {
                        ans = Func()(ans, st[i][l]);
                    }
                    l += 1 << i;
                }
            }
            return ans;
        }
    }
};