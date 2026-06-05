#include <bits/stdc++.h>
using namespace std;


int main() {
    int N = 3, K = 20;
    int mask = (1 << N) - 1;

    while(mask < (1 << K)) {
        int c = mask & -mask;
        int r = mask + c;
        mask = (((mask ^ r) >> 2) / c) | r;
    }
    return 0;
}