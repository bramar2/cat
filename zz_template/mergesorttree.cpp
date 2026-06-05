#include <bits/stdc++.h>
using namespace std;

template <class T>
struct MergeSortTree {
    int n;
    vector<vector<T>> tree;

    MergeSortTree(int size) : n(1) {
        while(n < size) n <<= 1;
        tree.resize(2*n, {});
    }

    template <typename Container>
    void build(const Container& arr) {
        for(int i = n; i < n + size(arr); i++)
            tree[i] = {arr[i - n]};
        build_from_leaves();
    }

    void _internal_upd(int i) {
        tree[i].clear();
        merge(begin(tree[i<<1]), end(tree[i<<1]), begin(tree[i<<1|1]), end(tree[i<<1|1]),
            back_inserter(tree[i]));
    }

    void build_from_leaves() {
        for(int i = n - 1; i > 0; i--) {
            _internal_upd(i);
        }
    }

    void update(int pos) {
        for(int idx = (n + pos) >> 1; idx > 0; idx >>= 1) {
            _internal_upd(idx);
        }
    }

    vector<T>& at(int x) {
        return tree[n + x];
    }

    template <typename Func>
    void query(int l, int r, const Func& F) {
        for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) F(tree[l++]);
            if(r & 1) F(tree[--r]);
        }
    }
};