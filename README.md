# CP-Resources
This is a collection of problems that I've collected from places for practice. I might add other resources later.
# Codeforces problems
[Leha and Function](https://codeforces.com/contest/841/problem/C) 

```cpp
#include "bits/stdc++.h"
using namespace std;

typedef pair<int, int> PII;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<PII> v(n);
    for (auto& [x, y] : v) cin >> x;
    for (auto& [x, y] : v) cin >> y;

    sort(v.begin(), v.end(),
         [](PII a, PII b) { return a.first - a.second > b.first - b.second; });

    int ans = 0;
    while (k--) {
        ans += v.back().first;
        v.pop_back();
    }

    while (not v.empty()) {
        auto [x, y] = v.back();
        ans += min(x, y);
        v.pop_back();
    }

    cout << ans << endl;
}


```

