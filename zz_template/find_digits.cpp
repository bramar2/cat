// for numbers 123456789101112....

#include <bits/stdc++.h>
using namespace std;


array<__int128, 17> TEN;

string tostr(__int128 x) {
    string ans;
    while(x > 0) {
        ans.push_back(char('0' + (x % 10)));
        x /= 10;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

__int128 digits(__int128 n) { // return digits count of all numbers <= n
    if(n < 10) return n;
    __int128 ans = 0, d = 1, cur = 9, cnt = 9;
    while(cur <= n) {
        ans += d * cnt;
        cur = 10*cur + 9, cnt *= 10, d++;
    }
    ans += d * (n - TEN[d - 1] + 1);
    return ans;
}

__int128 find(__int128 n, __int128 digit) {
    // count how many digits of digit appears of all numbers <= n, then multiply by digit itself
    string str = tostr(n);
    int sz = str.size();

    // <cnt_nums, cnt_digit>
    vector dp(sz + 1, vector(2, array<__int128, 2> {}));

    dp[sz][0] = dp[sz][1] = {1, 0};

    char chDigit = char('0' + digit);
    for(int idx = sz - 1; idx >= 0; idx--) {
        for(int tight = 0; tight <= 1; tight++) {
            for(char nxt = '0'; nxt <= '9'; nxt++) {
                if(tight && nxt > str[idx]) break;
                array<__int128, 2> cand = dp[idx + 1][tight && nxt == str[idx]];
                
                dp[idx][tight][0] += cand[0];
                dp[idx][tight][1] += cand[1];

                if(nxt == chDigit) dp[idx][tight][1] += cand[0];
            }
        }
    }

    __int128 cnt = dp[0][1][1];
    return digit * cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    TEN[0] = 1;
    for(int i = 1; i < size(TEN); i++) TEN[i] = 10 * TEN[i - 1];

    int t = 1;
    cin >> t;

    while(t--) {
        long long llk;
        cin >> llk;

        __int128 k = llk;

        __int128 l = 1, r = 8e13, q = -1;
        while(l <= r) {
            __int128 m = (l + r) / 2;
            if(digits(m) >= k) {
                q = m;
                r = m - 1;
            }else {
                l = m + 1;
            }
        }
        assert(q > 0);

        __int128 ans = 0;

        string str = to_string((long long) q);
        __int128 dcnt = digits(q);
        __int128 diff = dcnt - k;
        if(diff < 0) diff = -diff;

        q--;
        while(diff > 0) {
            str.pop_back();
            diff--;
        }
        for(char ch : str) {
            ans += (ch - '0');
        }

        for(int digit = 1; digit <= 9; digit++) {
            ans += find(q, digit);
        }

        cout << tostr(ans) << "\n";
    }

    return 0;
}