#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int TP_START = +1;
const int TP_END = -1;
struct ls_point {
    ll x, y;
    ls_point(ll x, ll y) : x(x), y(y) {}
};
struct ls_line {
    const ls_point p, q;
    int id;
    ls_line(ls_point p, ls_point q) : p(p), q(q) {}

    ll y_form(ll x) const {
        return p.y + (x - p.x) * (q.y-p.y)/(q.x-p.x);
    }
};
struct ls_event {
    ll x;
    int type; // 0=start, 1=end
    int id;
    ls_event(ll x, int type, int id) : x(x), type(type), id(id) {}
};
struct ls_event_cmp {
    bool operator()(const ls_event& a, const ls_event& b) {
        // Epsilon may be needed for decimal point lines
        return a.x < b.x || (a.x == b.x && a.type > b.type);
    }
};
ll opx;
bool operator<(const ls_line& a, const ls_line& b) {
    // ll x = max(min(a.p.x, a.q.x), min(b.p.x, b.q.x));
    // return a.y_form(x) < b.y_form(x);
    return a.y_form(opx) < b.y_form(opx);
}
struct line_cmp {
    bool operator()(const ls_line& a, const ls_line& b) const {
        ll x = max(min(a.p.x, a.q.x), min(b.p.x, b.q.x));
        return a.y_form(x) < b.y_form(x);
    }
};
bool intersect1d(ll l1, ll r1, ll l2, ll r2) {
    if(l1 > r1)
        swap(l1, r1);
    if(l2 > r2)
        swap(l2, r2);
    return max(l1, l2) <= min(r1, r2);
}
int vec(const ls_point& a, const ls_point& b, const ls_point& c) {
    ll s = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return abs(s) == 0 ? 0 : (s > 0 ? TP_START : TP_END);
}
bool intersect(const ls_line& a, const ls_line& b) {
    return intersect1d(a.p.x, a.q.x, b.p.x, b.q.x) &&
           intersect1d(a.p.y, a.q.y, b.p.y, b.q.y) &&
           vec(a.p, a.q, b.p) * vec(a.p, a.q, b.q) <= 0 &&
           vec(b.p, b.q, a.p) * vec(b.p, b.q, a.q) <= 0;
}
ll countIntersections(vector<ls_line>& lines) {
    int n = (int) lines.size();
    vector<ls_event> events;
    for(int i = 0; i < n; i++) {
        lines[i].id = i;
        events.push_back(ls_event(min(lines[i].p.x, lines[i].q.x), TP_START, i));
        events.push_back(ls_event(max(lines[i].p.x, lines[i].q.x), TP_END, i));
    }
    sort(events.begin(), events.end(), ls_event_cmp());
    set<ls_line> st;
    vector<set<ls_line>::iterator> where(n);
    ll ans = 0;

    auto itrNext = [](auto a) { return ++a; };
    auto itrPrev = [&](auto a) { return a == st.begin() ? st.end() : --a; };
    for(const ls_event& event : events) {
        int id = event.id;
        opx = event.id;
        if(event.type == TP_START) {
            auto next = st.lower_bound(lines[id]);
            auto prev = itrPrev(next);
            if(next != st.end() && intersect(*next, lines[id])) {
                ans++;
            }
            if(prev != st.end() && intersect(*prev, lines[id])) {
                ans++;
            }
            where[id] = st.insert(next, lines[id]);
        }else {
            auto next = itrNext(where[id]), prev = itrPrev(where[id]);
            if(next != st.end() && prev != st.end() && intersect(*next, *prev)) {
                ans++;
            }
            st.erase(where[id]);
        }
    }
    return ans;
}