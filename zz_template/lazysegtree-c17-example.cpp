constexpr long long MOD = 1e9 + 7;

template <class T, class Z>
struct default_apply_lazy {
    T operator() (T node, Z lazy, int len) const {
        return node + len * lazy;
    }
};

struct Node {
    // X = 0, Z = 1
    // cnt[startWithX/Z][endWithX/Z]
    long long cnt[2][2] {};
    long long ans = 0;
};

struct cmerge_node {
    Node operator() (const Node& a, const Node& b) const {
        if(a.ans == 0) return b;
        if(b.ans == 0) return a;
        Node res;
        res.ans = (a.ans + b.ans) % MOD;
        res.ans = (res.ans + 1LL * (a.cnt[0][0] + a.cnt[1][0]) * (b.cnt[1][0] + b.cnt[1][1])) % MOD;
        res.ans = (res.ans + 1LL * (a.cnt[0][1] + a.cnt[1][1]) * (b.cnt[0][0] + b.cnt[0][1])) % MOD;

        res.cnt[0][0] = (a.cnt[0][0] + b.cnt[0][0] + 1LL * a.cnt[0][1] * b.cnt[0][0] + 1LL * a.cnt[0][0] * b.cnt[1][0]) % MOD;
        res.cnt[0][1] = (a.cnt[0][1] + b.cnt[0][1] + 1LL * a.cnt[0][1] * b.cnt[0][1] + 1LL * a.cnt[0][0] * b.cnt[1][1]) % MOD;
        res.cnt[1][0] = (a.cnt[1][0] + b.cnt[1][0] + 1LL * a.cnt[1][1] * b.cnt[0][0] + 1LL * a.cnt[1][0] * b.cnt[1][0]) % MOD;
        res.cnt[1][1] = (a.cnt[1][1] + b.cnt[1][1] + 1LL * a.cnt[1][1] * b.cnt[0][1] + 1LL * a.cnt[1][0] * b.cnt[1][1]) % MOD;
        return res;
    }
};

struct cmerge_lazy {
    Node operator() (Node a, Node b) const {
        return b;
    }
};

struct capply_lazy {
    Node operator() (Node node, Node lazy, int len) const {
        return (lazy.ans == 0) ? node : lazy;
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
    Z default_lazy_value;

    LazySegmentTree(int size, T def = T()) : default_value(def) {
        n = (size == 1) ? 1 : (1 << (8 * sizeof(int) - __builtin_clz(size - 1)));
        h = sizeof(int) * 8 - 1 - __builtin_clz(n);
        tree.resize(2*n, default_value);
        lazy.resize(n, nullopt);
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

    void apply(int p, optional<Z> value) {
        if(!value.has_value()) return;
        tree[p] = apply_lazy()(tree[p], *value, segment(p));
        if(p < n) {
            lazy[p] = (lazy[p].has_value()) ? combine_lazy()(*lazy[p], *value) : *value;
        }
    }

    void build(int p) {
        while(p > 1) {
            p >>= 1;
            tree[p] = merge_node()(tree[p<<1], tree[p<<1|1]);
            if(lazy[p].has_value()) {
                tree[p] = apply_lazy()(tree[p], *lazy[p], segment(p));
            }
        }
    }

    void push(int p) {
        for(int s = h; s > 0; s--) {
            int i = p >> s;
            if(lazy[i].has_value()) {
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

constexpr Node DEF {};

Node get(char ch) {
    Node node;
    node.ans = 1;
    if(ch == 'x') {
        node.cnt[0][0]++;
    }else {
        node.cnt[1][1]++;
    }
    return node;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int n = s.size();
    int q;
    cin >> q;

    vector<Node> initial(n);
    for(int i = 0; i < n; i++) {
        initial[i] = get(s[i]);
    }
    LazySegmentTree<Node, Node, cmerge_node, cmerge_lazy, capply_lazy> segtree(n);
    segtree.build_from_container(initial);

    while(q--) {
        char ch;
        cin >> ch;
        if(ch == 'Q') {
            int l, r;
            cin >> l >> r;
            --l, --r;

            long long ans = segtree.query(l, r).ans;
            cout << ans << "\n";
        }else {
            int idx;
            cin >> idx;
            --idx;

            if(s[idx] == 'x') {
                s[idx] = 'z';
            }else {
                s[idx] = 'x';
            }

            segtree.update(idx, idx, get(s[idx]));
        }
    }

    return 0;
}