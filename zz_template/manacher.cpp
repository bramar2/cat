#include <bits/stdc++.h>
using namespace std;

class Manacher {
private:
    vector<int> odd, even;
    // cp-algorithms
    vector<int> manacher_odd(string s) {
        int n = s.size();
        s = "$" + s + "^";
        vector<int> p(n + 2);
        int l = 1, r = 1;
        for(int i = 1; i <= n; i++) {
            p[i] = max(0, min(r - i, p[l + (r - i)]));
            while(s[i - p[i]] == s[i + p[i]]) {
                p[i]++;
            }
            if(i + p[i] > r) {
                l = i - p[i], r = i + p[i];
            }
        }
        return vector<int>(begin(p) + 1, end(p) - 1);
    }
    string hashtag(const string& s) {
        // "abaab" -> "#a#b#a#a#b"
        // then to check for even length palindromes
        // you check the longest palindrome radius centered at a #
        // for example "abaab" -> "baab" is a palindrome
        // #b#a#a#b#
        //     ^
        // then for a certain i, it is to check 2*(i+1)
        int n = s.length();
        string r = string(2*n+1, '#');
        for(int i = 0; i < n; i++) {
            r[2*i+1] = s[i];
        }
        return r;
    }
public:
    Manacher(const string& s) : odd(manacher_odd(s)), even(manacher_odd(hashtag(s))) {}

    bool is_palindrome(int left, int right) const {
        if(left > right) return false;
        int len = right-left+1, mid = (left + right) / 2;
        if(len % 2 == 1) {
            return palindrome_radius_odd(mid) >= (len+1)/2;
        }else {
            return palindrome_radius_even(mid) >= len/2;
        }
    }

    int palindrome_radius_odd(int middle) const {
        return odd[middle];
    }
    int palindrome_radius_even(int middleLeft) const {
        int r = even[2*(middleLeft + 1)];
        // # -> radius 0 [internal_radius 1]
        // a#a -> #a#a# -> radius 1 [internal_radius 3]
        // #a#a#a#a# -> radius 2 [internal_radius 5]
        return (r-1)/2;
    }
};