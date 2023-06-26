/* RMQ for - Square Queries
 * K = side of the square is 2^k
 */

#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using PII = pair<int, int>;

const int N = 505;
const int K = 10;

int st[N][N][K];
int n, q;

int bit(int n) { return 1 << n; }

void processRMQ() {
    for (int k = 1; bit(k) <= n; k++) {
        for (int i = 1; i + bit(k) - 1 <= n; i++) {
            for (int j = 1; j + bit(k) - 1 <= n; j++) {
                int x = i + bit(k - 1), y = j + bit(k - 1);
                st[i][j][k] = max(st[i][j][k - 1], st[i][y][k - 1]);
                st[i][j][k] = max(st[i][j][k], max(st[x][j][k - 1], st[x][y][k - 1]));
            }
        }
    }
}

// upper left corner, size of a side
int get(int i, int j, int d) {
    int k = (int)log2(d), x = i + d - 1, y = j + d - 1, m1, m2;
    m1 = max(st[i][j][k], st[i][y - bit(k) + 1][k]);
    m2 = max(st[x - bit(k) + 1][j][k], st[x - bit(k) + 1][y - bit(k) + 1][k]);
    return max(m1, m2);
}


// solves https://lightoj.com/problem/square-queries
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t, cs = 0;
    cin >> t;

    while (t--) {
        cout << "Case " << ++cs << ":\n";

        cin >> n >> q;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> st[i][j][0];
            }
        }

        processRMQ();

        while (q--) {
            int x, y, l;
            cin >> x >> y >> l;

            cout << get(x, y, l) << "\n";
        }
    }
}

