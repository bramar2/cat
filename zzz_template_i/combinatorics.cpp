#include <bits/stdc++.h>
using namespace std;

class CombPrime;
constexpr int MAXN = 200'001;
constexpr int MAXMOD = 1e6;
map<int, CombPrime> prime_comb_map;

long long ext_euclidean(long long a, long long b, long long& x, long long& y) {
    x = 1, y = 0;
    long long x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        long long q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}
long long mod_inv(long long n, long long _mod) {
    long long x, y;
    ext_euclidean(n, _mod, x, y);
    return (x % _mod + _mod) % _mod;
}
long long mod_exp(long long base, long long exp, long long _mod) {
    long long ans = 1;
    base %= _mod;
    while(exp > 0) {
        if(exp & 1) ans = (base*ans) % _mod;
        exp /= 2;
        base = (base*base) % _mod;
    }
    return ans;
}

class CombLargePrime {
public:
    const long long MOD;
    vector<long long> fact, invfact;
    CombLargePrime(long long _MOD, int compute = MAXN) :
        MOD(_MOD),
        fact(vector<long long>(compute + 1, 1)),
        invfact(vector<long long>(compute + 1, 1)) {

        for(int i = 1; i <= compute; i++) {
            fact[i] = (i * fact[i - 1]) % MOD;
            invfact[i] = (mod_exp(i, MOD-2, MOD) * invfact[i - 1]) % MOD;
        }
    }

    long long comb(int N, int K) const {
        return fact[N] * invfact[K] % MOD * invfact[N-K] % MOD;
    }
};
class CombPrime {
public:
    const long long p, b, MOD;
    vector<long long> p_cnt, powers, fact, invfact;
    CombPrime() : p(-1), b(-1), MOD(-1) {}
    CombPrime(long long _p, int compute = MAXN) :
        p(_p),
        b(floor(log2(MAXMOD + 1)/log2(_p))),
        MOD(powl(_p, b)),
        p_cnt(vector<long long>(compute + 1, 0)),
        powers(vector<long long>(b + 1, 1)),
        fact(vector<long long>(compute + 1, 1)),
        invfact(vector<long long>(compute + 1, 1)) {

        for(int i = 1; i <= b; i++) {
            powers[i] = p * powers[i - 1];
        }

        for(int i = 1; i <= compute; i++) {
            p_cnt[i] = p_cnt[i - 1];

            int x = i;
            while(x % p == 0) p_cnt[i]++, x /= p;

            fact[i] = (x * fact[i - 1]) % MOD;
            invfact[i] = (mod_inv(x, MOD) * invfact[i - 1]) % MOD;
        }
    }
    long long comb(int N, int K, int exp = 1) const {
        if(p_cnt[N] - p_cnt[K] - p_cnt[N-K] >= exp) return 0LL;
        return fact[N] * invfact[K] % powers[exp] * invfact[N-K] % powers[exp];
    }
};
class CombCompound {
public:
    vector<pair<int, int>> factors;
    int f_sz;
    CombCompound(int N, int compute = MAXN) {
        for(long long i = 2; i * i <= N; i++) {
            if(N % i != 0) continue;
            int exp = 0;
            while(N % i == 0) {
                exp++;
                N /= i;
            }
            factors.push_back({(int) i, exp});
        }
        if(N > 1) factors.push_back({N, 1});
        for(auto& factor : factors) {
            if(!prime_comb_map.count(factor.first)) {
                prime_comb_map.emplace(factor.first, CombPrime(factor.first));
            }
        }
        f_sz = factors.size();
    }

    long long comb(int N, int K) const {
        if(f_sz == 0) return 0;
        long long a1, m1;
        for(int i = 0; i < f_sz; i++) {
            long long a2 = prime_comb_map[factors[i].first].comb(N, K, factors[i].second);
            long long m2 = powl(factors[i].first, factors[i].second);
            if(i == 0) {
                a1 = a2;
                m1 = m2;
            }else {
                a1 = a1 * mod_inv(m2, m1) * m2 + a2 * mod_inv(m1, m2) * m1;
                m1 = m1 * m2;
                a1 %= m1;
            }
        }
        return a1;
    }
};
const int MOD = 1e9 + 7;
const CombLargePrime comb(MOD);