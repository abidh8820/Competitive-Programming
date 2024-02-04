#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using PII = pair<int, int>;

const int N = 1007;
const int M = 10056;

int C[N][N];
int dp[N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  for (int i = 0; i < N; i++) C[i][0] = 1;

  for (int i = 1; i < N; i++) {
    for (int j = 1; j <= i; j++) {
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % M;
    }
  }


  int t, cs = 0;
  cin >> t;

  while (t--) {
    cout << "Case " << ++cs << ": ";
    int n;
    cin >> n;

    cout << dp[n] << "\n";
  }
}

