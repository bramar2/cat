#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50001;
vector<int> divisors[MAXN + 1] {};

auto init = []() {
    for(int d = 1; d <= MAXN; d++) {
        for(int i = d; i <= MAXN; i += d) {
            divisors[i].push_back(d);
        }
    }
    return 0;
}();

struct GcdDS {
    int cnt = 0;
    set<pair<int,int>> freqs;
    map<int, int> div;

    void upd(int x, int delta) {
        if(div[x]) freqs.erase({div[x], x});
        div[x] += delta;
        if(div[x]) freqs.insert({div[x], x});
    }

    void add(int x) {
        cnt++;
        for(int sq : divisors[x]) {
            upd(sq, 1);
        }
    }

    void rmv(int x) {
        cnt--;
        for(int sq : divisors[x]) {
            upd(sq, 1);
        }
    }

    int gcd() {
        return freqs.rbegin()->second;
    }
};