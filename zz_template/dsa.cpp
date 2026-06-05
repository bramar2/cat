#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

struct custom_hash {
    static size_t splitmix64(long long x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(long long x) const {
        static const long long FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

class ListNodeA {
public:
    int val;
    ListNodeA* next;
    ListNodeA() {}
    ListNodeA(int x) : val(x) {}
    ListNodeA(int x, ListNodeA* pNext) : val(x), next(pNext) {}
};
class TreeNodeA {
public:
    int val;
    TreeNodeA* left;
    TreeNodeA* right;
    TreeNodeA(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNodeA(int x, TreeNodeA* left, TreeNodeA* right) : val(x), left(left), right(right) {}
};
struct TrieNode {
    int val = INT_MAX;
    TrieNode* children[26] {};
    ~TrieNode() {
        for(const auto& node : children) {
            delete node;
        }
    }
};
struct Trie {
    TrieNode* children[26] {};
    void insert(const std::string& word, int cost) {
        TrieNode* last;
        if(children[word[0]-'a'] != nullptr) {
            last = children[word[0]-'a'];
        }else {
            last = (children[word[0]-'a'] = new TrieNode());
        }
        for(size_t i = 1; i < word.size(); i++) {
            int k = word[i] - 'a';
            if(last->children[k] != nullptr) {
                last = last->children[k];
            }else {
                last = (last->children[k] = new TrieNode());
            }
        }
        if(cost < last->val) {
            last->val = cost;
        }
    }
};
// Segment Tree template with leafNodes
struct SegmentTree {
    vector<int> tree;
    vector<int> leafNodes;
    int size;
    // Empty 0 SegmentTree
    explicit SegmentTree(int n) : tree(vector<int>(2*n-1, 0)), leafNodes(vector<int>()), size(n) {}
    explicit SegmentTree(vector<int>& nums) : tree(vector<int>(2*nums.size()-1, 0)), leafNodes(vector<int>()), size((int) nums.size()) {
        build(nums, 0, (int) nums.size()-1, 0);
    }
    int build(vector<int>& nums, int numsLeft, int numsRight,
            int treeIndex) {
        if(numsLeft == numsRight) {
            leafNodes.push_back(treeIndex);
            tree[treeIndex] = nums[numsLeft];
            return nums[numsLeft];
        }
        // Divide into two
        int mid = numsLeft + (numsRight - numsLeft) / 2;

        int sum = build(nums, numsLeft, mid, left(treeIndex)) +
            build(nums, mid+1, numsRight, right(treeIndex));
        tree[treeIndex] = sum;
        return sum;
    }
    int query(int left, int right) {
        return _queryRec(0, left, right, 0, size-1);
    }
    void update(int idx, int target) {
        return updateOffset(idx, target-tree[leafNodes[idx]]);
    }
    void updateOffset(int idx, int offset) {
        int node = leafNodes[idx];
        while(true) {
            tree[node] += offset;
            if(node == 0) break;
            node = parent(node);
        }
    }
    int _queryRec(int treeIndex, int qLeft, int qRight, int treeLeft, int treeRight) {
        if(qLeft <= treeLeft && qRight >= treeRight) return tree[treeIndex];
        if(treeRight < qLeft || treeLeft > qRight) return 0;

        int mid = treeLeft + (treeRight - treeLeft) / 2;
        return _queryRec(left(treeIndex), qLeft, qRight, treeLeft, mid) +
            _queryRec(right(treeIndex), qLeft, qRight, mid+1, treeRight);

    }
    int parent(int x) { return (x-1) / 2; }
    int left(int x) { return 2*x+1; }
    int right(int x) { return 2*x+2; }
};
struct UnionFind {
    vector<int> parent, rank;
    explicit UnionFind(int n) : parent(vector<int>(n)), rank(vector<int>(n, 1)) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int node) {
        if(node == parent[node]) return node;
        return parent[node] = find(parent[node]);
    }
    bool unionize(int node1, int node2) {
        int p1 = find(node1);
        int p2 = find(node2);
        if(p1 == p2) return false; // Same parent
        if(rank[p1] >= rank[p2]) {
            // Append p2 under p1
            parent[p2] = p1;
            rank[p1] += rank[p2];
        }else {
            parent[p1] = p2;
            rank[p2] += rank[p1];
        }
        return true;
    }
};
long long stirlingSecondKind(int n, int k) {
    static vector<vector<long long>> memo(1001, vector<long long>(1001, -1));
    if(n < k) return 0;
    if(k == 1) return 1;
    if(memo[n][k] != -1) return memo[n][k];
    // return memo[n][k] = (k * (stirlingSecondKind(n - 1, k) + stirlingSecondKind(n - 1, k - 1)) % MOD);
    return memo[n][k] = (k * (stirlingSecondKind(n - 1, k) + stirlingSecondKind(n - 1, k - 1)));
}
// void bronKerbosch(long long& ans, long long curr, vector<unordered_set<int>>& adj,
// unordered_set<int>& candidates, unordered_set<int>& exclusionSet) {
//     // cout << "Clique(" << curr << ",candidates={";
//     // for(int c : candidates) cout << c << ',';
//     // cout << "},exclusionSet={";
//     // for(int c : exclusionSet) cout << c << ',';
//     // cout << "})" << endl;
//     if(candidates.empty()) {
//         if(exclusionSet.empty())
//             ans = max(ans, curr);
//         return;
//     }
//     unordered_set<int>& neighborsOfPivot = adj[*candidates.begin()];
//     for(auto itr = candidates.begin(); itr != candidates.end();) {
//         if(neighborsOfPivot.find(*itr) != neighborsOfPivot.end()) {
//             itr++;
//             continue;
//         }
//         unordered_set<int> copyCandidates, copyExclusion;
//         set_intersection(all(candidates), all(adj[*itr]), inserter(copyCandidates, copyCandidates.begin()));
//         set_intersection(all(exclusionSet), all(adj[*itr]), inserter(copyExclusion, copyExclusion.begin()));
//         clique(ans, curr+1, adj, copyCandidates, copyExclusion);
//         exclusionSet.insert(*itr);
//         itr = candidates.erase(itr);
//     }
// }
//V2 Works
// void clique(long long& ans, long long curr, vector<unordered_set<int>>& adj,
// unordered_set<int>& candidates, unordered_set<int>& exclusionSet) {
//     if(candidates.empty() && exclusionSet.empty()) {
//         ans = max(ans, curr);
//         return;
//     }
//     int pivot = candidates.empty() ? *exclusionSet.begin() : *candidates.begin();
//     unordered_set<int> tmp(candidates);
//     for(int neighbor : adj[pivot]) tmp.erase(neighbor);
//     for(int vert : tmp) {
//         unordered_set<int> copyCandidates, copyExclusion;
//         for(int p : adj[vert]) {
//             if(candidates.find(p) != candidates.end()) copyCandidates.insert(p);
//             if(exclusionSet.find(p) != exclusionSet.end()) copyExclusion.insert(p);
//         }
//         clique(ans, curr+1, adj, copyCandidates, copyExclusion);
//         candidates.erase(vert);
//         exclusionSet.insert(vert);
//     }
// }
// struct pt {
//     double x, y;
// };

// struct line {
//     double a, b, c;
// };

// const double EPS = 1e-9;

// double det(double a, double b, double c, double d) {
//     return a*d - b*c;
// }

// bool intersect(line m, line n, pt & res) {
//     double zn = det(m.a, m.b, n.a, n.b);
//     if (abs(zn) < EPS)
//         return false;
//     res.x = -det(m.c, m.b, n.c, n.b) / zn;
//     res.y = -det(m.a, m.c, n.a, n.c) / zn;
//     return true;
// }

// bool parallel(line m, line n) {
//     return abs(det(m.a, m.b, n.a, n.b)) < EPS;
// }

// bool equivalent(line m, line n) {
//     return abs(det(m.a, m.b, n.a, n.b)) < EPS
//         && abs(det(m.a, m.c, n.a, n.c)) < EPS
//         && abs(det(m.b, m.c, n.b, n.c)) < EPS;
// }

