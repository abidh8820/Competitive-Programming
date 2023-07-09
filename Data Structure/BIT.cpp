
#include "bits/stdc++.h"
using namespace std;

struct BIT {  // 1-indexed
    int n;
    vector<int> ft;
    BIT(int n_) {
        n = n_ + 5;
        ft.assign(n, 0);
    }
    void update(int idx, int val) {
        for (; idx < n; idx += idx & -idx) ft[idx] += val;
    }
    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx) sum += ft[idx];
        return sum;
    }
    int query(int i, int j) { return query(j) - query(i - 1); }
};

