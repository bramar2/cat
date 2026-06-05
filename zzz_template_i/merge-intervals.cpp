#include <bits/stdc++.h>
using namespace std;


vector<vector<int>>& mergeIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    });
    int ressz = 1;
    for(int i = 1, intervalsSz = intervals.size(); i < intervalsSz; i++) {
        if(intervals[i][0] <= intervals[ressz-1][1]) {
            intervals[ressz-1][1] = max(intervals[ressz-1][1], intervals[i][1]);
        }else {
        	intervals[ressz++] = (intervals[i]);
        }
    }
    intervals.resize(ressz);
    return intervals;
}