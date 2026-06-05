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
vector<vector<long long>>& mergeIntervals(vector<vector<long long>>& intervals) {
    sort(intervals.begin(), intervals.end(), [](const vector<long long>& a, const vector<long long>& b) {
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

vector<pair<int,int>>& mergeIntervals(vector<pair<int,int>>& intervals) {
    sort(intervals.begin(), intervals.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.first < b.first;
    });
    int ressz = 1;
    for(int i = 1, intervalsSz = intervals.size(); i < intervalsSz; i++) {
        if(intervals[i].first <= intervals[ressz-1].second) {
            intervals[ressz-1].second = max(intervals[ressz-1].second, intervals[i].second);
        }else {
            intervals[ressz++] = (intervals[i]);
        }
    }
    intervals.resize(ressz);
    return intervals;
}