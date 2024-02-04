//solves https://lightoj.com/problem/investigation
#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using PII = pair<int, int>;

int dp[11][2][2][1001][91];

vector<int> L, R;

int call(int pos, bool loose_low, bool loose_hi, int sum, int digsum, int k) {
    if (pos == R.size()) return (sum == 0 && digsum == 0);
    int &ret = dp[pos][loose_low][loose_hi][sum][digsum];

    if (~ret) return ret;
    ret = 0;

    int lo = L[pos], hi = R[pos];
    if (loose_low) lo = 0;
    if (loose_hi) hi = 9;

    for (int i = lo; i <= hi; i++) {
        bool n_loose_hi = loose_hi | (R[pos] > i);
        bool n_loose_low = loose_low | (i > L[pos]);

        int new_sum = (sum * 10 + i) % k;
        int new_dsum = (digsum + i) % k;

        ret += call(pos + 1, n_loose_low, n_loose_hi, new_sum, new_dsum, k);
    }

    return ret;
}

int main() {
    int t, cs = 0;

    cin >> t;
    while (t--) {
        cout << "Case " << ++cs << ": ";
        memset(dp, -1, sizeof dp);

        string A, B;
        int K;
        cin >> A >> B >> K;

        reverse(A.begin(), A.end());
        reverse(B.begin(), B.end());
        int mx = max(A.size(), B.size());

        while (A.size() < mx) A += '0';
        while (B.size() < mx) B += '0';

        reverse(A.begin(), A.end());
        reverse(B.begin(), B.end());

        R.resize(mx), L.resize(mx);

        for (int i = 0; i < mx; i++) {
            R[i] = B[i] - '0';
            L[i] = A[i] - '0';
        }

        if (K >= 100) {
            cout << 0 << "\n";
            continue;
        }

        cout << call(0, 0, 0, 0, 0, K) << "\n";
    }
}

