#include <bits/stdc++.h>
using namespace std;

template<typename T, auto merge_node>
struct DynamicSegmentTree {
    struct Node {
        int left = -1, right = -1;
        T val {};
    };

    vector<Node> nodes;
    int root0;
    int n;

    int assign(Node node) { nodes.push_back(node); return nodes.size() - 1; }

    DynamicSegmentTree(int size) {
        n = size;
        root0 = assign({ .left = -1, .right = -1 });
    }

    template <typename Func>
    void update(int root, int vl, int vr, int pos, const Func& apply) {
        if(vl == vr) {
            nodes[root].val = apply(nodes[root].val, vl, vr);
            return;
        }

        if(nodes[root].left == -1) {
            nodes[root].left = assign({ .left = -1, .right = -1 });
            nodes[root].right = assign({ .left = -1, .right = -1 });
        }

        int m = (vl + vr) / 2;
        if(pos <= m) {
            update(nodes[root].left, vl, m, pos, apply);
        }else {
            update(nodes[root].right, m + 1, vr, pos, apply);
        }

        nodes[root].val = merge_node(nodes[nodes[root].left].val, nodes[nodes[root].right].val);
    }

    template <typename Func>
    void update(int pos, const Func& apply) {
        update(root0, 0, n - 1, pos, apply);
    }

    T query(int root, int vl, int vr, int l, int r) {
        if(vr < l || vl > r) return T {};
        if((l <= vl && vr <= r) || nodes[root].left == -1) return nodes[root].val;

        int m = (vl + vr) / 2;
        return merge_node(query(nodes[root].left, vl, m, l, r), query(nodes[root].right, m + 1, vr, l, r));
    }

    T query(int l, int r) {
        return query(root0, 0, n - 1, l, r);
    }
};