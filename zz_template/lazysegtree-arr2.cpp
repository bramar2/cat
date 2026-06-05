#include <bits/stdc++.h>
using namespace std;


typedef long long T;
constexpr long long MAXN = 500'001;
const T segtree_def = 0LL;
T segtree[4*MAXN];
T lazy[4*MAXN];
long long segtreeN;

void segtree_init(long long N) {
	fill(segtree, segtree + 4*N, segtree_def);
	fill(lazy, lazy + 4*N, segtree_def);
	segtreeN = N;
}

T segtree_merge(const T& a, const T& b) {
	return (a + b);
}
T segtree_range_sum(const T& a, long long length) {
	return length * a;
}
T segtree_lazy_merge(const T& a, const T& b) {
	return (a + b);
}
bool segtree_is_default(const T& a) {
	return a == segtree_def;
}

void segtree_propagate(long long v, long long vl, long long vr) {
	if(!segtree_is_default(lazy[v])) {
		segtree[v] = segtree_merge(segtree[v], segtree_range_sum(lazy[v], vr-vl+1));

		if(vl != vr) {
			lazy[2*v] = segtree_lazy_merge(lazy[2*v], lazy[v]);
			lazy[2*v+1] = segtree_lazy_merge(lazy[2*v+1], lazy[v]);
		}

		lazy[v] = segtree_def;
	}
}

void segtree_update(long long pos, T val) {
	function<void(long long, long long, long long)> upd = [&](long long v, long long vl, long long vr) {
		segtree_propagate(v, vl, vr);
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
void segtree_update_range(long long l, long long r, T val) {
	function<void(long long, long long, long long)> upd = [&](long long v, long long vl, long long vr) {
		segtree_propagate(v, vl, vr);
		if(r < vl || vr < l) {
			return;
		}else if(l <= vl && vr <= r) {
			lazy[v] = segtree_lazy_merge(lazy[v], val);
		}else {
			long long intersectionLen = min(vr, r) - max(vl, l);
			segtree[v] += segtree_range_sum(val, intersectionLen);

			long long vmid = vl + (vr-vl)/2;
			upd(2*v, vl, vmid);
			upd(2*v+1, vmid+1, vr);
		}
	};
	upd(1, 0, segtreeN-1);
}

T segtree_query(long long l, long long r) {
	function<T(long long, long long, long long)> q = [&](long long v, long long vl, long long vr) -> T {
		if(vr < l || r < vl) return segtree_def;
		segtree_propagate(v, vl, vr);
		if(l <= vl && vr <= r) return segtree[v];
		long long vmid = vl + (vr-vl)/2;
		return segtree_merge(q(2*v, vl, vmid), q(2*v+1, vmid+1, vr));
	};
	return q(1, 0, segtreeN-1);
}