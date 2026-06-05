#include <bits/stdc++.h>
using namespace std;


struct UnionFind {
    vector<int> parent, size;
    explicit UnionFind(int n) : parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    explicit UnionFind(const UnionFind& other) : parent(other.parent), size(other.size) {}

    int find(int node) {
        if(node == parent[node]) return node;
        return parent[node] = find(parent[node]);
    }
    bool unite(int node1, int node2) {
        int p1 = find(node1);
        int p2 = find(node2);
        if(p1 == p2) return false;
        if(size[p1] < size[p2]) swap(p1, p2);
        parent[p2] = p1;
        size[p1] += size[p2];
        return true;
    }
};