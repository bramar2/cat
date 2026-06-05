#include <bits/stdc++.h>
using namespace std;

int main() {
    deque<int> q;
    auto add = [&](int e) {
        while(!q.empty() && q.back() > e) {
            q.pop_back();
        }
        q.push_back(e);
    };
    auto remove = [&](int e) {
        if(!q.empty() && q.front() == e)
            q.pop_front();
    };
    auto minimum = [&]() {
        return q.front();
    };
    add(2);
    add(4);
    add(3);
    // After this, you can only pop [2,4,3] in order first

    cout << "Minimum: " << q.front() << '\n';
    remove(2);
    cout << "Minimum: " << q.front() << '\n';
    remove(4);
    cout << "Minimum: " << q.front() << '\n';
    return 0;
}