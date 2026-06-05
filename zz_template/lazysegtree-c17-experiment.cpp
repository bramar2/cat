#include <bits/stdc++.h>
using namespace std;

template <class T, class Z>
struct default_apply_lazy {
    T operator() (T node, Z lazy, int len) const {
        return node + len * lazy;
    }
};

template <class T>
struct cmerge_node {
    T operator() (T a, T b) const {
        return a + b;
    }
};

template <class Z>
struct cmerge_lazy {
    Z operator() (Z a, Z b) const {
        return a + b;
    }
};

template <class T, class Z>
struct capply_lazy {
    T operator() (T node, Z lazy, int len) const {
        return node + len * lazy;
    }
};

// https://codeforces.com/blog/entry/18051
template <class T, class Z = T,
    class merge_node = plus<T>,
    class combine_lazy = plus<Z>,
    class apply_lazy = default_apply_lazy<T, Z>>
struct LazySegmentTree {
    int n, h;
    vector<T> tree;
    vector<optional<Z>> lazy;

    T default_value;

    LazySegmentTree(int size, T def = T()) : default_value(def) {
        n = (size == 1) ? 1 : (1 << (8 * sizeof(int) - __builtin_clz(size - 1)));
        h = sizeof(int) * 8 - 1 - __builtin_clz(n);
        tree.resize(2*n, default_value);
        lazy.resize(n);
    }


    template <typename Container>
    void build_from_container(const Container& arr) {
        copy(begin(arr), end(arr), begin(tree) + n);
        build_from_leaves();
    }

    void build_from_leaves() {
        for(int i = n - 1; i > 0; i--) tree[i] = merge_node()(tree[i<<1], tree[i<<1|1]);
    }

    
    int segment(int p) {
        return n >> (sizeof(int) * 8 - 1 - __builtin_clz(p));
    }

    void apply(int p, Z value) {
        tree[p] = apply_lazy()(tree[p], value, segment(p));
        if(p < n) lazy[p] = lazy[p] ? combine_lazy()(lazy[p], value) : value;
    }

    void build(int p) {
        while(p > 1) {
            p >>= 1;
            tree[p] = apply_lazy()(merge_node()(tree[p<<1], tree[p<<1|1]), lazy[p], segment(p));
        }
    }

    void push(int p) {
        for(int s = h; s > 0; s--) {
            int i = p >> s;
            if(lazy[i]) {
                apply(i<<1, lazy[i]);
                apply(i<<1|1, lazy[i]);
                lazy[i] = nullopt;
            }
        }
    }

    void update(int l, int r, Z value) {
        l += n, r += n + 1;
        int l0 = l, r0 = r;
        for(; l < r; l >>= 1, r >>= 1) {
            if(l & 1) apply(l++, value);
            if(r & 1) apply(--r, value);
        }
        build(l0);
        build(r0 - 1);
    }

    T query(int l, int r) {
        l += n, r += n + 1;
        push(l);
        push(r - 1);
        T resLeft = default_value, resRight = default_value;
        for(; l < r; l >>= 1, r >>= 1) {
            if(l & 1) resLeft = merge_node()(resLeft, tree[l++]);
            if(r & 1) resRight = merge_node()(tree[--r], resRight);
        }
        return merge_node()(resLeft, resRight);
    }
};