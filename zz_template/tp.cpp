#include <bits/stdc++.h>
using namespace std;


// no idea what this DS is
template <typename T = int>
struct Tp {
    static constexpr T DEFAULT = -189142891;
    int n;
    vector<int> parent, size, left, right;
    vector<T> values;

    explicit Tp(int c_n) : n(c_n), values(n), parent(n), size(n, 1), left(n), right(n) {
        iota(parent.begin(), parent.end(), 0);
        iota(left.begin(), left.end(), 0);
        iota(right.begin(), right.end(), 0);
    }

    template <typename Container>
    void build(const Container& arr) {
        copy(begin(arr), end(arr), begin(values));
    }

    inline const T nval(int a, int b) const {
        return values[a] + values[b];
    }

    template <typename F>
    bool adj_info(int node, const F& func) {
        node = _find(node);
        int l = left[node], r = right[node];
        if(l > 0) {
            func(_find(l - 1), node);
        }
        if(r < n - 1) {
            func(node, _find(r + 1));
        }
        return l > 0 || r < n - 1;
    }
    template <typename F>
    bool edge_info(int l, int r, const F& func) { // [p, l, r, q], then info will return [p,l], [r,q]
        l = _find(l), r = _find(r);
        int ll = left[l], rr = right[r];
        if(ll > 0) {
            func(_find(ll - 1), l);
        }
        if(rr < n - 1) {
            func(r, _find(rr + 1));
        }
        return ll > 0 || rr < n - 1;
    }

    bool merge_left(int node, T newVal = DEFAULT) {
        int a = _find(node);
        if(left[a] == 0)
            return false;
        int b = _find(left[a] - 1);
        return merge(b, a, newVal);
    }

    bool merge_right(int node, T newVal = DEFAULT) {
        int a = _find(node);
        if(right[a] == n - 1)
            return false;
        int b = _find(right[a] + 1);
        return merge(a, b, newVal);
    }

    bool merge(int a, int b, T newVal = DEFAULT) {
        if(newVal == DEFAULT) newVal = nval(a, b);
        int nleft = left[a], nright = right[b];
        if(!_unite(a, b)) return false;
        int p = _find(a);
        left[p] = nleft, right[p] = nright, values[p] = newVal;
        return true;
    }

    int prev(int node) {
        node = _find(node);
        int l = left[node];
        return (l == 0) ? -1 : _find(l - 1);
    }

    int next(int node) {
        node = _find(node);
        int r = right[node];
        return (r == n - 1) ? -1 : _find(r + 1);
    }

    int _find(int node) {
        if(node == parent[node]) return node;
        return parent[node] = _find(parent[node]);
    }

    bool _unite(int node1, int node2) {
        int p1 = _find(node1), p2 = _find(node2);
        if(p1 == p2) return false;
        if(size[p1] < size[p2]) swap(p1, p2);
        parent[p2] = p1;
        size[p1] += size[p2];
        return true;
    }

    T& operator[](int idx) {
        return values[_find(idx)];
    }
};