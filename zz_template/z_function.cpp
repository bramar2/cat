#include <bits/stdc++.h>
using namespace std;


class ZFunction {
private:
	int patternSize;
	vector<int> z;
	// cp-algorithms (modified)
	vector<int> z_function(const string& s) {
	    int n = s.size();
	    z.resize(n);
	    int l = 0, r = 0;
	    for(int i = 1; i < n; i++) {
	        if(i < r) {
	            z[i] = min(r - i, z[i - l]);
	        }
	        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
	            z[i]++;
	        }
	        if(i + z[i] > r) {
	            l = i;
	            r = i + z[i];
	        }
	    }
	    return z;
	}
public:
	ZFunction(const string& text, const string& pattern) : patternSize(pattern.size()) {
		z_function(pattern + (char)(1) + text);
	}

	int match_len(int text_idx) {
		return z[patternSize + text_idx + 1];
	}
};
vector<int> z_function(const string& s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}