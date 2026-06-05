#include <bits/stdc++.h>
using namespace std;

istream& operator>>(istream& is, __int128& n) { 
    string s;
    is >> s;

    n = 0;
    int start = 0;
    bool sign = false;
    if(s[0] == '-') {
        start++, sign = true;
    }
    for(int i = start, sz = s.size(); i < sz; i++) {
        int val = (s[i] - '0');
        assert(0 <= val && val <= 9);
        n = 10 * n + val;
    }
    if(sign) n *= -1;

    return is;
}

ostream& operator<<(ostream& stream, __int128 n) {
    if(n == 0) {
        stream << 0;
        return stream;
    }
    if(n < 0) {
        stream << "-";
        n = -n;
    }
    string s;
    while(n > 0) {
        s += char('0' + (n % 10));
        n /= 10;
    }
    reverse(s.begin(), s.end());
    stream << s;
    return stream;
}