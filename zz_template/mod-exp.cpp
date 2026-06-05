#include <bits/stdc++.h>
using namespace std;

long long mod_exp(long long base, int exp, long long mod) {
	long long ans = 1;
	base %= mod;
	while(exp > 0) {
		if(exp & 1) ans = (ans * base) % mod;
		exp >>= 1;
		base = (base * base) % mod;
	}
	return ans;
}

constexpr long long MOD = 1e9 + 7;;
long long mod_exp(long long base, int exp) {
	long long ans = 1;
	base %= MOD;
	while(exp > 0) {
		if(exp & 1) ans = (ans * base) % MOD;
		exp >>= 1;
		base = (base * base) % MOD;
	}
	return ans;
}
long long mod_inv(long long base) {
	return mod_exp(base, MOD - 2);
}