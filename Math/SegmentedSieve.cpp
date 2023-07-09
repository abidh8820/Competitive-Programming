/* Segmented Sieve*/

#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using PII = pair<int, int>;

const int N = 1e6 + 7;

int bpf[N];
vector<int> primes;

void sieve() {
    for (int i = 2; i < N; i++) {
        if (bpf[i] == 0) {
            primes.push_back(i);
            for (int j = i; j < N; j += i) bpf[j] = i;
        }
    }
}

int cntPrime(LL l, LL r) {
    if (l < 2) l = 2;

    if (l > r) return 0;
    vector<bool> flag(r - l + 1, true);

    for (LL p : primes) {
        if (p * p > r) break;
        LL now = (l / p) * p;

        if (now < l) now += p; 
        if (now < 2 * p) now = 2 * p; 

        for (LL cur = now; cur <= r; cur += p) {
            flag[cur - l] = 0;
        }
    }

    int cnt = 0;
    for (int i = 0; i <=r-l; i++) cnt += flag[i];
    return cnt;
}

//solves https://lightoj.com/problem/help-hanzo
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    sieve();

    int t, cs = 0;
    cin >> t;

    while (t--) {
        cout << "Case " << ++cs << ": ";
        LL l, r;
        cin >> l >> r;

        cout << cntPrime(l, r) << "\n";
    }
}

