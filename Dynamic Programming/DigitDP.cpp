#include <bits/stdc++.h>
using namespace std;
 
using LL = long long;
 
int L[25], R[25];
int dp[30][10][10][2][2][2];

// lead == 0 , all leading zeros so far 
//starting from MSB to .. LSB (numbers are reversed)

int call(int pos, int mx, int mn, int strict_low, int strict_high, int lead) {
    if (pos <= 0) return mx - mn;
    int &r = dp[pos][mx][mn][strict_low][strict_high][lead];
    if (~r) return r;
 
    int lo = strict_low ? L[pos] : 0;
    int hi = strict_high ? R[pos] : 9;
 
    r = 10;
    for (int dig = lo; dig <= hi; dig++) {
        int new_sl = strict_low & (dig == L[pos]);
        int new_sh = strict_high & (dig == R[pos]);
        int new_lead = (lead | (dig > 0));
 
        int new_mx = new_lead ? max(dig, mx) : mx;
        int new_mn = new_lead ? min(dig, mn) : mn;
        r = min(r, call(pos - 1, new_mx, new_mn, new_sl, new_sh, new_lead));
    }
    return r;
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--) {
        string a, b;
        cin >> a >> b;

        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());

        memset(L, 0, sizeof L);
        memset(R, 0, sizeof R);

        for (int i = 1; i <= a.size(); i++) L[i] = a[i - 1] - '0';
        for (int i = 1; i <= b.size(); i++) R[i] = b[i - 1] - '0';

        memset(dp, -1, sizeof dp);
        cout << call(20, 0, 9, 1, 1, 0) << "\n";
    }
}

