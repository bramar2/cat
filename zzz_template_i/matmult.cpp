#include <bits/stdc++.h>
using namespace std;

void matmult(const vector<vector<long long>>& A, const vector<vector<long long>>& B, vector<vector<long long>>& res) {
	assert(A[0].size() == B.size());

	int n = B.size(), rows = A.size(), cols = B[0].size();
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			for(int k = res[i][j] = 0; k < n; k++) {
				// res[i][j] += A[i][k] * B[k][j];
				res[i][j] = (res[i][j] + A[i][k] * B[k][j]) % MOD;
			}
		}
	}
}

// O(N^3 * log n)
vector<vector<long long>> matpow(vector<vector<long long>> base, vector<vector<long long>> transformation, long long n) {
	vector<vector<long long>> tmp_base = base;
	vector<vector<long long>> tmp_transformation = transformation;
	while(n > 0) {
		if(n & 1) {
			matmult(base, transformation, tmp_base);
			swap(base, tmp_base);
		}
		n >>= 1;
		matmult(transformation, transformation, tmp_transformation);
		swap(transformation, tmp_transformation);
	}
	return base;
}