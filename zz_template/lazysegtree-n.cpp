#include <bits/stdc++.h>
using namespace std;

template <typename T, T default_value = T(), T default_lazy = T()>
struct LazySegmentTree {
    int sz;
    vector<T> tree, lazy;

    LazySegmentTree(int n) : 
        sz(n), tree(4*n, default_value), lazy(4*n, default_lazy) {}

    inline T merge_children(const T& a, const T& b) {
        return a + b;
    }
    inline T merge_with_lazy(const T& a, const T& val, bool isLeaf) {
        return a + val;
    }
    inline T combine_lazy(const T& v1, const T& v2) {
        return v1 + v2;
    }
    inline T lazy_range(const T& val, int length) {
        return val * length;
    }

    template <typename Container>
    void build(const Container& arr) {
        return build(arr, 1, 0, sz-1);
    }
    template <typename Container>
    void build(const Container& arr, int v, int vl, int vr) {
        if(vl == vr) {
            tree[v] = arr[vl];
        }else {
            int vmid = (vl + vr) / 2;
            build(arr, 2*v, vl, vmid);
            build(arr, 2*v+1, vmid+1, vr);
            tree[v] = merge_children(tree[2*v], tree[2*v+1]);
        }
    }

    void propagate(int v, int vl, int vr) {
        if(lazy[v] == default_lazy) return;
        tree[v] = merge_with_lazy(tree[v], lazy_range(lazy[v], vr - vl + 1), vl == vr);

        if(vl != vr) {
            lazy[2*v] = combine_lazy(lazy[2*v], lazy[v]);
            lazy[2*v+1] = combine_lazy(lazy[2*v+1], lazy[v]);
        }

        lazy[v] = default_lazy;
    }

    void update(int pos, T val) {
        update(pos, val, 1, 0, sz-1);
    }
    void update(int pos, T& val, int v, int vl, int vr) {
        propagate(v, vl, vr);
        if(vl == vr) {
            tree[v] = val;
        }else {
            int vmid = (vl + vr) / 2;
            if(pos <= vmid) {
                update(pos, val, 2*v, vl, vmid);
            }else {
                update(pos, val, 2*v+1, vmid+1, vr);
            }
            tree[v] = merge_children(tree[2*v], tree[2*v+1]);
        }
    }
    void update_range(int l, int r, T val) {
        update_range(l, r, val, 1, 0, sz-1);
    }
    void update_range(int l, int r, T& val, int v, int vl, int vr) {
        propagate(v, vl, vr);
        if(r < vl || vr < l) return;
        if(l <= vl && vr <= r) {
            tree[v] = merge_with_lazy(tree[v], lazy_range(val, vr - vl + 1), false);
            if(vl != vr) {
                lazy[2*v] += val;
                lazy[2*v + 1] += val;
            }
        }else {
            int vmid = (vl + vr) / 2;
            update_range(l, r, val, 2*v, vl, vmid);
            update_range(l, r, val, 2*v+1, vmid+1, vr);
            tree[v] = merge_children(tree[2*v], tree[2*v + 1]);
        }
    }
    T query(int l, int r) {
        return query(l, r, 1, 0, sz-1);
    }
    T query(int x) {
        return query(x, x);
    }
    T query(int l, int r, int v, int vl, int vr) {
        propagate(v, vl, vr);
        if(vr < l || r < vl) return default_value;
        if(l <= vl && vr <= r) return tree[v];
        int vmid = (vl + vr) / 2;
        return merge_children(query(l, r, 2*v, vl, vmid), query(l, r, 2*v+1, vmid+1, vr));
    }
};