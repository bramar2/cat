#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

mt19937 mt(chrono::high_resolution_clock::now().time_since_epoch().count());

typedef long long ll;
typedef long double ld;
typedef __int128 int128_t;
typedef unsigned __int128 uint128_t;

#define dbg_stream cerr
void __print(int x) {dbg_stream << x;}
void __print(long x) {dbg_stream << x;}
void __print(long long x) {dbg_stream << x;}
void __print(unsigned x) {dbg_stream << x;}
void __print(unsigned long x) {dbg_stream << x;}
void __print(unsigned long long x) {dbg_stream << x;}
void __print(float x) {dbg_stream << x;}
void __print(double x) {dbg_stream << x;}
void __print(long double x) {dbg_stream << x;}
void __print(char x) {dbg_stream << '\'' << x << '\'';}
void __print(const char *x) {dbg_stream << '\"' << x << '\"';}
void __print(const string &x) {dbg_stream << '\"' << x << '\"';}
void __print(bool x) {dbg_stream << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {dbg_stream << '{'; __print(x.first); dbg_stream << ','; __print(x.second); dbg_stream << '}';}
template<typename T>
void __print(const T &x) {int f = 0; dbg_stream << '{'; for (auto &i: x) dbg_stream << (f++ ? "," : ""), __print(i); dbg_stream << "}";}
void _print() {dbg_stream << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) dbg_stream << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define dbg(x...) dbg_stream << "[" << #x << "] = ["; _print(x)
#else
#define dbg(x...)
#endif

template <typename T>
void print(T t) { int f = 0; for(const auto& b : t) cout << (f++ ? " " : "") << b; cout << '\n'; }
template <typename T>
void print2d(T t) { for(const auto& b : t) { print(b); } }

void solve() {
    
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    cin >> t;
    for(int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}