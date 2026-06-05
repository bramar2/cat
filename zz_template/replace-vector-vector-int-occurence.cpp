#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500'001;
int idx_a[MAXN], idx_b[MAXN], a[MAXN], b[MAXN], fa[MAXN], fb[MAXN], ha[MAXN], hb[MAXN], indices[3 * MAXN];
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while(T--) {
        int n;
        cin >> n;

        for(int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
        }
        for(int i = 0; i < n; i++) {
            cin >> b[i];
            b[i]--;
        }

        fill(fa, fa + n, 1);
        fill(fb, fb + n, 1);
        for(int x : a) fa[x]++;
        for(int x : b) fb[x]++;

        int cur_idx = 0;
        for(int i = 0; i < n; cur_idx += fa[i++]) {
            ha[i] = cur_idx;
        }

        for(int i = 0; i < n; cur_idx += fb[i++]) {
            hb[i] = cur_idx;
        }

        copy(ha, ha + n, fa);
        copy(hb, hb + n, fb);
        // reuse f for ptrs

        for(int i = 0; i < n; i++) {
            indices[fa[a[i]]++] = i;
            indices[fb[b[i]]++] = i;
        }
        
        for(int i = 0; i < n; i++) {

        }


        // vector indices_a(n, deque<int>(1, n)), indices_b(n, deque<int>(1, n));
        // for(int i = n - 1; i >= 0; i--) {
        //     indices_a[a[i]].push_front(i);
        //     indices_b[b[i]].push_front(i);
        // }

        deque<int> diff;
        for(int i = 0; i < n; i++) {
            if(i > 0) {
                while(indices_a[i].front() < idx_a[i - 1]) indices_a[i].pop_front();
            }
            idx_a[i] = indices_a[i].front();
        }

        for(int i = 0; i < n; i++) {
            if(i > 0) {
                while(indices_b[i].front() < idx_b[i - 1]) indices_b[i].pop_front();
            }
            idx_b[i] = indices_b[i].front();
        }

        for(int i = 0; i < n; i++) {
            if(idx_a[i] != idx_b[i]) {
                diff.push_back(i);
            }
        }

        long long ans = 0;

        for(int l = 0; l < n; l++) {
            int r = n;
            if(!diff.empty()) r = min(idx_a[diff[0]], idx_b[diff[0]]);
            ans += r - l;

            // delete index `l`
            while(indices_a[a[l]].front() <= l) indices_a[a[l]].pop_front();
            while(indices_b[b[l]].front() <= l) indices_b[b[l]].pop_front();

            int upd = -1;

            for(int i = 0; i < n && (i == 0 || idx_a[i] < idx_a[i - 1]); upd = ++i) {
                if(i > 0) {
                    while(indices_a[i].front() < idx_a[i - 1]) indices_a[i].pop_front();
                }
                idx_a[i] = indices_a[i].front();
            }
            for(int i = 0; i < n && (i == 0 || idx_b[i] < idx_b[i - 1]); upd = max(upd, ++i)) {
                if(i > 0) {
                    while(indices_b[i].front() < idx_b[i - 1]) indices_b[i].pop_front();
                }
                idx_b[i] = indices_b[i].front();
            }
            while(!diff.empty() && diff.front() < upd) diff.pop_front();
            for(int i = upd - 1; i >= 0; i--) {
                if(idx_a[i] != idx_b[i]) {
                    diff.push_front(i);
                }
            }
        }

        cout << ans << "\n";
    }

    return 0;
}