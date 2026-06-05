#include <bits/stdc++.h>
using namespace std;


typedef long long T;
constexpr long long MAXN = 200'000;
constexpr T segtree_def = 0LL;
T segtree[4*MAXN];
long long segtreeN;

void segtree_init(long long N) {
	fill(segtree, segtree + 4*N, segtree_def);
	segtreeN = N;
}

T segtree_merge(const T& a, const T& b) {
	return a + b;
}

void segtree_update(long long pos, T val) {
	auto upd = [&](this auto&& upd, long long v, long long vl, long long vr) -> void {
		if(vl == vr) {
			segtree[v] = val;
		}else {
			long long vmid = vl + (vr-vl)/2;
			if(pos <= vmid) {
				upd(2*v, vl, vmid);
			}else {
				upd(2*v+1, vmid+1, vr);
			}
			segtree[v] = segtree_merge(segtree[2*v], segtree[2*v+1]);
		}
	};
	upd(1, 0, segtreeN-1);
}

T segtree_query(long long l, long long r) {
	auto q = [&](this auto&& q, long long v, long long vl, long long vr) -> T {
		if(l <= vl && vr <= r) return segtree[v];
		if(vr < l || r < vl) return segtree_def;
		long long vmid = vl + (vr-vl)/2;
		return segtree_merge(q(2*v, vl, vmid), q(2*v+1, vmid+1, vr));
	};
	return q(1, 0, segtreeN-1);
}