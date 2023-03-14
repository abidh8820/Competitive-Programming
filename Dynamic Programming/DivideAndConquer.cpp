/*
* Divide and Conquer Optimization
* Must satisfy : Opt(i,j) <= Opt(i,j+1)
*/

#include <bits/stdc++.h>
using namespace std;

cnst int N = 100007;
using LL = long long;

const LL INF = 1e17;

LL DW[N], D[N], W[N];
int n;

LL Cost(int l, int r) {
    LL nem = DW[r - 1] - DW[l - 1];
    LL denom = (D[n] - D[r - 1]) * (W[r - 1] - W[l - 1]);
    return nem - denom;
}

vector<LL> dp_before(N), dp_cur(N);
void compute(int l, int r, int optl, int optr) {
    if (l > r) return;

    int mid = (l + r) >> 1;
    LL best = INF, opt = -1;

    for (int k = optl; k <= min(mid, optr); k++) {
        LL cur = (k ? dp_before[k - 1] : 0) + Cost(k, mid);
        if (cur < best) best = cur, opt = k;
    }

    dp_cur[mid] = best;
    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}


//solves https://szkopul.edu.pl/problemset/problem/ovRIpLFK3IhyFPjnVXeZtGxH/site/?key=statement

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> W[i] >> D[i];
    }

    LL totD = 0;
    for (int i = n; i >= 1; i--) {
        totD += D[i];
        DW[i] = totD * W[i];
    }
    for (int i = 1; i <= n; i++) {
        DW[i] += DW[i - 1];
        D[i] += D[i - 1];
        W[i] += W[i - 1];
    }

    for (int i = 1; i <= n; i++) dp_before[i] = Cost(1, i);

    for (int i = 2; i <= 3; i++) {
        compute(1, n + 1, 1, n + 1);
        dp_before = dp_cur;
    }

    cout << dp_before[n + 1] << endl;
}
