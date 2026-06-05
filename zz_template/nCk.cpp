#include <bits/stdc++.h>
using namespace std;

long long nCk(int N, int K) {
	if(K > N) return 0;
	if(K > N-K) K = N-K;
	long long ans = 1;
	for(long long i = 1; i <= K; i++)
		ans = (ans * (N - (K-i))) / i;
	return ans;
}