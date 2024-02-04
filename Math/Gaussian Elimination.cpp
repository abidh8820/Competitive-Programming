#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using PII = pair<int, int>;

const int N = 3e5 + 9;

const double EPS = 1e-9;

int Gauss(vector<vector<double>> a, vector<double> &ans) {
  int n = (int)a.size(), m = (int)a[0].size() - 1;
  vector<int> pos(m, -1);

  double det = 1;
  int rank = 0;

  for (int col = 0, row = 0; col < m && row < n; ++col) {
    int mx = row;
    for (int i = row; i < n; i++)
      if (fabs(a[i][col]) > fabs(a[mx][col])) mx = i;
    if (fabs(a[mx][col]) < EPS) {
      det = 0;
      continue;
    }

    for (int i = col; i <= m; i++) swap(a[row][i], a[mx][i]);
    if (row != mx) det = -det;
    det *= a[row][col], pos[col] = row;

    for (int i = 0; i < n; i++) {
      if (i != row && fabs(a[i][col]) > EPS) {
        double c = a[i][col] / a[row][col];
        for (int j = col; j <= m; j++) a[i][j] -= a[row][j] * c;
      }
    }
    ++row, ++rank;
  }

  ans.assign(m, 0);
  for (int i = 0; i < m; i++) {
    if (pos[i] != -1) ans[i] = a[pos[i]][m] / a[pos[i]][i];
  }
  for (int i = 0; i < n; i++) {
    double sum = 0;
    for (int j = 0; j < m; j++) sum += ans[j] * a[i][j];
    if (fabs(sum - a[i][m]) > EPS) return -1;  // no solution
  }

  for (int i = 0; i < m; i++)
    if (pos[i] == -1) return 2;  // infinte solutions
  return 1;                      // unique solution
}

//solves https://lightoj.com/problem/snakes-and-ladders

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int t, cs = 0;
  cin >> t;

  while (t--) {
    cout << "Case " << ++cs << ": ";
    int n;
    cin >> n;

    vector<int> to(100, -1);
    for (int i = 1; i <= n; i++) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      to[a] = b;
    }

    vector<vector<double>> mat(101, vector<double>(101, 0));
    for (int i = 0; i < 100; i++) {
      if (to[i] != -1) {
        mat[i][i] = 1, mat[i][to[i]] = -1;
        continue;
      }

      mat[i][i] = -1;
      for (int j = 1; j <= 6; j++) {
        if (i + j < 100) mat[i][i + j] += 1.0 / 6;
        else mat[i][i] += 1.0 / 6;
      }
      mat[i][100] = -1;
    }

    vector<double> ans(100);
    cerr << (Gauss(mat, ans)) << endl;

    cout << fixed<<setprecision(10)<<ans[0] << "\n";
  }
}

