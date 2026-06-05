#include <bits/stdc++.h>
using namespace std;


template <typename T = int>
class LazySegmentTree {
public:
	int size;
	vector<T> tree;
	vector<T> lazy;
	explicit LazySegmentTree(int n) : size(n), tree(vector<T>(4*n+1,0)), lazy(vector<T>(4*n+1,0)) {}
	explicit LazySegmentTree(int n, const vector<T>& v) : size(n),
		tree(vector<T>(4*n+1,0)), lazy(vector<T>(4*n+1,0)) {
		build(v, 1, 0, size-1);
	}
	void build(const vector<T>& nums, int vertex, int l, int r) {
		if(l == r) {
			tree[vertex] = nums[l];
		}else {
			int mid = l + (r-l)/2;
			build(nums, 2*vertex, l, mid);
			build(nums, 2*vertex+1, mid+1, r);
			
			tree[vertex] = tree[2*vertex] + tree[2*vertex+1];
		}
	}
	T query(int l, int r) {
		return query_internal(1, 0, size-1, l, r);
	}
	T query_internal(int vertex, int vl, int vr, int l, int r) {
		if(lazy[vertex] != 0) {
			
			tree[vertex] += lazy[vertex] * (vr - vl + 1);
			if(vl != vr) {
				lazy[2*vertex] += lazy[vertex];
				lazy[2*vertex+1] += lazy[vertex];
			}
			lazy[vertex] = 0;
		}
		if(l <= vl && vr <= r)
            return tree[vertex];
        if(vr < l || r < vl)
        	return 0;
		
		int vmid = vl + (vr-vl)/2;
		
		return query_internal(2*vertex, vl, vmid, l, r) +
			query_internal(2*vertex+1, vmid+1, vr, l, r);
	}
	void update_range(int l, int r, T val) {
		update_range_internal(1, 0, size-1, l, r, val);
	}
	void update_range_internal(int vertex, int vl, int vr, int l, int r, T val) {
		if(l > r || (vl < l && vr < l) || (r < vl && r < vr)) {
			return;
		}
		if(l <= vl && vl <= vr && vr <= r) {
			lazy[vertex] += val;
		}else {
			int vmid = vl + (vr-vl)/2;
			update_range_internal(2*vertex, vl, vmid, l, r, val);
			update_range_internal(2*vertex+1, vmid+1, vr, l, r, val);
		}
	}
	void update(int pos, T val) {
		update_internal(1, 0, size-1, pos, val);
	}
	void update_internal(int vertex, int vl, int vr, int pos, T val) {
		if(vl == vr) {
			tree[vertex] = val;
		}else {
			long long vmid = vl + (vr-vl)/2;
			if(pos <= vmid) {
				update_internal(2*vertex, vl, vmid, pos, val);
			}else {
				update_internal(2*vertex+1, vmid+1, vr, pos, val);
			}
			
			tree[vertex] = tree[2*vertex] + tree[2*vertex+1];
		}
	}
};