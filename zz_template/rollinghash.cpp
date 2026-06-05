#include <bits/stdc++.h>
using namespace std;

inline long long mod_exp(long long base, long long exp, long long modd) { unsigned long long ans = 1; base %= modd; while(exp > 0) { if(exp%2==1) ans = (base*ans)%modd; exp /= 2; base = (base*base)%modd; } return ans; }


int rolling_hash_parse_char(char ch) {
	return (ch - 'a' + 1);
}

class RollingHash {
private:
	int n; long long base, modulo;
	vector<long long> forward_hash, backward_hash, pow, inv_pow;
	void computePow() {
		if(n == 0) return;
		pow.resize(n + 1); inv_pow.resize(n + 1);
		pow[0] = inv_pow[0] = 1;
		long long invBase = mod_exp(base, modulo-2, modulo);
		for(int i = 1; i <= n; i++) {
			pow[i] = (base * pow[i - 1]) % modulo;
			inv_pow[i] = (invBase * inv_pow[i - 1]) % modulo;
		}
	}
	void computeForwards(const string& s) {
		if(n == 0) return;
		forward_hash.resize(n);
		forward_hash[0] = rolling_hash_parse_char(s[0]);
		for(int i = 1; i < n; i++) {
			forward_hash[i] = (forward_hash[i - 1] + pow[i] * rolling_hash_parse_char(s[i])) % modulo;
		}
	}
	void computeBackwards(const string& s) {
		if(n == 0) return;
		backward_hash.resize(n);
		backward_hash[n-1] = rolling_hash_parse_char(s[n-1]);
		for(int i = n-2; i >= 0; i--) {
			backward_hash[i] = (backward_hash[i + 1] + pow[n-i-1] * rolling_hash_parse_char(s[i])) % modulo;
		}
	}
public:
	RollingHash(const string& s,
		bool reversed = false,
		long long base = 67,
		long long modulo = 1'000'000'007) : n(s.size()), base(base), modulo(modulo) {
		computePow();
		computeForwards(s);
		if(reversed)
			computeBackwards(s);
	}

	long long get(int left, int right) const {
		long long res;
		if(left <= right) {
			if(left == 0) return forward_hash[right];
			res = (forward_hash[right] - forward_hash[left - 1]) * inv_pow[left];
		}else {
			if(left == n-1) return backward_hash[right];
			res = (backward_hash[right] - backward_hash[left + 1]) * inv_pow[n-left-1];
		}
		res %= modulo;
		if(res < 0) res += modulo;
		return res;
	}
	bool palindrome(int left, int right) const {
		return get(left, right) == get(right, left);
	}
};

class RollingHashSet {
private:
	vector<RollingHash> hashes;
public:
	RollingHashSet(const string& s, const vector<pair<int,int>>& hash) {
		if(hash.empty()) throw;
		hashes.reserve(hash.size());
		for(int i = 0, n = hash.size(); i < n; i++) {
			hashes.push_back(RollingHash(s, true, hash[i].first, hash[i].second));
		}
	}
	long long get(int i, int left, int right) const {
		return hashes[i].get(left, right);
	}
	bool palindrome(int left, int right) const {
		bool val = true;
		for(const RollingHash& h : hashes) {
			val &= (h.get(left, right) == h.get(right, left));
			if(!val) break;
		}
		return val;
	}
};