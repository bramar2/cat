#include <bits/stdc++.h>
using namespace std;

template <long long MOD = 1e9 + 7, bool MOD_PRIME = true>
class modint {
private:
	// static const long long MOD = 1e9 + 7;
	// static const bool MOD_PRIME = true;
	long long val;

	static inline long long sanitize(long long val) { val %= MOD; if(val < 0) val += MOD; return val; }
	static long long inv(long long n) { return inv_coprime(n); }
	static long long inv_coprime(long long n) { return MOD_PRIME ? mod_exp(n, MOD-2) : inv_ext_euclidean(n); }
	// credit extended euclidean: https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
	static long long inv_ext_euclidean(long long n) {
		long long x, y;
		ext_euclidean(n, MOD, x, y);
		return (x % MOD + MOD) % MOD;
	}
	static long long ext_euclidean(long long a, long long b, long long& x, long long& y) {
		x = 1, y = 0;
	    int x1 = 0, y1 = 1, a1 = a, b1 = b;
	    while (b1) {
	        int q = a1 / b1;
	        tie(x, x1) = make_tuple(x1, x - q * x1);
	        tie(y, y1) = make_tuple(y1, y - q * y1);
	        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
	    }
	    return a1;
	}
	static long long mod_exp(long long base, long long exp) {
		long long ans = 1; base %= MOD;
		while(exp > 0) {
			if(exp & 1) {
				ans = (base*ans) % MOD;
			}
			exp >>= 1;
			base = (base*base) % MOD;
		}
		return ans;
	}
public:
	modint() : val(0) {}
	template<typename Signed,
             std::enable_if_t<std::is_integral<Signed>::value && std::is_signed<Signed>::value, bool> = true>
	modint(Signed val) : val(sanitize(static_cast<long long>(val))) {}
	template<typename Unsigned,
             std::enable_if_t<std::is_integral<Unsigned>::value && !std::is_signed<Unsigned>::value, bool> = true>
	modint(Unsigned val) : val(sanitize(static_cast<long long>(val % MOD))) {}

	friend ostream& operator<<(ostream& stream, const modint n) {
		stream << n.val;
		return stream;
	}
	friend istream& operator>>(istream& stream, modint& n) {
		stream >> n.val;
		n.val = sanitize(n.val);
		return stream;
	}

	modint<MOD, MOD_PRIME>& operator++() { val = sanitize(val + 1); return *this; }
	modint<MOD, MOD_PRIME>& operator--() { val = sanitize(val - 1); return *this; }
	modint<MOD, MOD_PRIME> operator++(int) { auto old = *this; operator++(); return old; }
	modint<MOD, MOD_PRIME> operator--(int) { auto old = *this; operator--(); return old; }

	friend modint<MOD, MOD_PRIME> operator+(const modint<MOD, MOD_PRIME> lhs, const modint<MOD, MOD_PRIME> rhs) { return modint<MOD, MOD_PRIME>(lhs.val + rhs.val); }
	friend modint<MOD, MOD_PRIME> operator-(const modint<MOD, MOD_PRIME> lhs, const modint<MOD, MOD_PRIME> rhs) { return modint<MOD, MOD_PRIME>(lhs.val - rhs.val); }
	friend modint<MOD, MOD_PRIME> operator*(const modint<MOD, MOD_PRIME> lhs, const modint<MOD, MOD_PRIME> rhs) { return modint<MOD, MOD_PRIME>(lhs.val * rhs.val); }
	friend modint<MOD, MOD_PRIME> operator/(const modint<MOD, MOD_PRIME> lhs, const modint<MOD, MOD_PRIME> rhs) { if(rhs == 0) throw; return modint<MOD, MOD_PRIME>(lhs.val * inv(rhs.val)); }
	friend bool operator==(const modint<MOD, MOD_PRIME> lhs, const modint<MOD, MOD_PRIME> rhs) { return (lhs.val == rhs.val); }
	friend bool operator!=(const modint<MOD, MOD_PRIME> lhs, const modint<MOD, MOD_PRIME> rhs) { return (lhs.val != rhs.val); }
	friend bool operator<(const modint<MOD, MOD_PRIME> lhs, const modint<MOD, MOD_PRIME> rhs) { return (lhs.val < rhs.val); }
	friend bool operator<=(const modint<MOD, MOD_PRIME> lhs, const modint<MOD, MOD_PRIME> rhs) { return (lhs.val <= rhs.val); }
	friend bool operator>(const modint<MOD, MOD_PRIME> lhs, const modint<MOD, MOD_PRIME> rhs) { return (lhs.val > rhs.val); }
	friend bool operator>=(const modint<MOD, MOD_PRIME> lhs, const modint<MOD, MOD_PRIME> rhs) { return (lhs.val >= rhs.val); }

	modint<MOD, MOD_PRIME>& operator+=(const modint<MOD, MOD_PRIME> rhs) { this->val = sanitize(this->val + rhs.val); return *this; }
	modint<MOD, MOD_PRIME>& operator-=(const modint<MOD, MOD_PRIME> rhs) { this->val = sanitize(this->val - rhs.val); return *this; }
	modint<MOD, MOD_PRIME>& operator*=(const modint<MOD, MOD_PRIME> rhs) { this->val = sanitize(this->val * rhs.val); return *this; }
	modint<MOD, MOD_PRIME>& operator/=(const modint<MOD, MOD_PRIME> rhs) { if(rhs == 0) throw; this->val = sanitize(this->val * inv(rhs.val)); return *this; }

	long long value() const {
		return val;
	}
};