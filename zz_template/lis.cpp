int lis_2d(vector<array<int, 2>>& points) {
    vector<array<int, 2>> res;
    sort(points.begin(), points.end(),
        [&](const auto& a, const auto& b) -> bool { return pair(a[0], -a[1]) < pair(b[0], -b[1]); });
    for(auto& point : points) {
        if(res.empty() || (point[0] > res.back()[0] && point[1] > res.back()[1])) {
            res.push_back(point);
        }else {
            int L = 0, R = res.size() - 1, Q = -1;
            while(L <= R) {
                int M = (L + R) / 2;
                if(point[0] > res[M][0] && point[1] > res[M][1]) {
                    Q = M;
                    L = M + 1;
                }else {
                    R = M - 1;
                }
            }
            res[Q + 1] = point;
        }
    } 
    return res.size();
}