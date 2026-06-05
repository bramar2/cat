#include <bits/stdc++.h>
using namespace std;

struct IntervalContainer {
    set<pair<int,int>> st;

    void oninsert(int l, int r) { }
    void onerase(int l, int r) { }

    void insert(int l, int r) {
        while(true) {
            if(auto it = st.lower_bound({r + 1, 0}); it != st.begin()) {
                --it;
                if(it->second >= l - 1) {
                    onerase(it->first, it->second);
                    l = min(l, it->first);
                    r = max(r, it->second);
                    st.erase(it);
                }else break;
            }else break;
        }

        if(auto it = st.lower_bound({r + 1, 0}); it != st.end() && it->first == r + 1) {
            onerase(it->first, it->second);
            r = max(r, it->second);
            st.erase(it);
        }

        oninsert(l, r);
        st.insert({l, r});
    }

    void erase(int l, int r) {
        while(true) {
            if(auto it = st.lower_bound({r + 1, 0}); it != st.begin()) {
                --it;
                if(it->second >= l) {
                    auto [tl, tr] = *it;
                    onerase(max(l, tl), min(tr, r));
                    st.erase(it);
                    if(tl <= l - 1) st.insert({tl, l - 1});
                    if(r + 1 <= tr) st.insert({r + 1, tr});
                }else break;
            }else break;
        }
    }

    bool count(int x) {
        if(auto it = st.lower_bound({x + 1, 0}); it != st.begin() && prev(it)->second >= x)
            return true;
        return false;
    }
    bool count(int l, int r) {
        if(auto it = st.upper_bound({r + 1, 0}); it != st.begin()) {
            if(--it; it->first <= l && r <= it->second)
                return true;
        }
        return false;
    }
};