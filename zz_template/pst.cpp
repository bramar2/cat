#include <bits/stdc++.h>
using namespace std;

template<typename T, auto merge_node>
struct PersistentSegmentTree {
    struct Node {
        int left, right;

        T info;
    };

    vector<Node> nodes;
    int root0;
    int n;

    int assign(Node node) { nodes.push_back(node); return nodes.size() - 1; }

    PersistentSegmentTree(int size) {
        n = size;
        root0 = build(0, n - 1);
    }

    int build(int l, int r) {
        if(l == r) return assign({ .left = -1, .right = -1 });

        int m = (l + r) / 2;
        return assign({
            .left = build(l, m), .right = build(m + 1, r)
        });
    }

    template <typename Func>
    int update(int root, int l, int r, int pos, const Func& apply) {
        if(l == r) return assign({ .left = -1, .right = -1, .info = apply(nodes[root].info) });
        int m = (l + r) / 2;

        Node node;
        if(pos <= m) {
            node.left = update(nodes[root].left, l, m, pos, apply);
            node.right = nodes[root].right;
        }else {
            node.left = nodes[root].left;
            node.right = update(nodes[root].right, m + 1, r, pos, apply);
        }
        node.info = merge_node(nodes[node.left].info, nodes[node.right].info);
        return assign(node);
    }

    template <typename Func>
    int update(int root, int pos, const Func& apply) {
        return update(root, 0, n - 1, pos, apply);
    }

    int update(int root, int pos, T new_val) {
        return update(root, 0, n - 1, pos, [&](const T& info) { return new_val; });
    }
};