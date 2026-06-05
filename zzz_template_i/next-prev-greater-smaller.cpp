#include <bits/stdc++.h>
using namespace std;

/*
compute(nums, nextGreater, [](int a, int b) { return a > b; }, false);
compute(nums, prevGreater, [](int a, int b) { return a >= b; }, true);
compute(nums, nextSmaller, [](int a, int b) { return a < b; }, false);
compute(nums, prevSmaller, [](int a, int b) { return a <= b; }, true);
*/
void compute(auto& nums, auto& res, const auto& cmp, bool reverse) {
    int n = nums.size();
    vector<int> stk;
    for(int i = reverse ? n-1 : 0, delta = reverse ? -1 : +1; 0 <= i && i < n; i += delta) {
        while(!stk.empty() && cmp(nums[i], nums[stk.back()])) {
            res[stk.back()] = i;
            stk.pop_back();
        }
        stk.push_back(i);
    }
}
void usage(auto& nums, auto& nextGreater, auto& nextSmaller, auto& prevGreater, auto& prevSmaller) {
    compute(nums, nextGreater, [](int a, int b) { return a > b; }, false);
    compute(nums, prevGreater, [](int a, int b) { return a >= b; }, true);
    compute(nums, nextSmaller, [](int a, int b) { return a < b; }, false);
    compute(nums, prevSmaller, [](int a, int b) { return a <= b; }, true);

    compute(nums, nextGreater, greater<>(), false);
    compute(nums, prevGreater, greater_equal<>(), true);
    compute(nums, nextSmaller, less<>(), false);
    compute(nums, prevSmaller, less_equal<>(), true);
}