#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

struct Hashing {
    vector<vector<int>> hs;
    vector<int> PWX, PWY;
    int n, m;

    static const int PX = 3731,  PY = 2999, mod = 998244353;
    Hashing() {}
    
    Hashing(vector<string>& s) {
        n = (int)s.size(), m = (int)s[0].size();
        hs.assign(n + 1, vector<int>(m + 1, 0));
        PWX.assign(n + 1, 1);
        PWY.assign(m + 1, 1);
        for (int i = 0; i < n; i++) PWX[i + 1] = 1LL * PWX[i] * PX % mod;
        for (int i = 0; i < m; i++) PWY[i + 1] = 1LL * PWY[i] * PY % mod;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                hs[i + 1][j + 1] = s[i][j] - 'a' + 1;
            }
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < m; j++) {
                hs[i][j + 1] = (hs[i][j + 1] + 1LL * hs[i][j] * PY % mod) % mod;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= m; j++) {
                hs[i + 1][j] = (hs[i + 1][j] + 1LL * hs[i][j] * PX % mod) % mod;
            }
        }
    }
    
    int get_hash(int x1, int y1, int x2, int y2) {
        assert(1 <= x1 && x1 <= x2 && x2 <= n);
        assert(1 <= y1 && y1 <= y2 && y2 <= m);
        x1--;
        y1--;
        int dx = x2 - x1, dy = y2 - y1;
        return (1LL * (hs[x2][y2] - 1LL * hs[x2][y1] * PWY[dy] % mod + mod) % mod -
            1LL * (hs[x1][y2] - 1LL * hs[x1][y1] * PWY[dy] % mod + mod) % mod * PWX[dx] % mod + mod) % mod;
    }
    
    int get_hash() {
        return get_hash(1, 1, n, m);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int r, c;
    cin >> r >> c;

    vector<string> pattern(r);
    for(auto& s : pattern) cin >> s;


    int n, m;
    cin >> n >> m;
    vector<string> hayStack(n);

    for(int i = 0; i < n; i++) {
        cin >> hayStack[i];
    }

    Hashing hayStackHash(hayStack), patternHash(pattern);
    vector<vector<int>> good(n, vector<int>(m, 0));

    int patHash = patternHash.get_hash();

    for(int i = 0; i  + r - 1< n; i++) {
        for(int j = 0; j + c - 1 < m; j++) {
            if(hayStackHash.get_hash(i + 1, j + 1, i + r , j + c) == patHash) {
                good[i][j]++;
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++) {
            if(i) good[i][j] += good[i - 1][j];
            if(j) good[i][j] += good[i][j - 1];
            if(i && j) good[i][j] -= good[i - 1][j - 1];
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int val = good[i][j];
            if(i - r >= 0) val -= good[i - r ][j];
            if(j - c >= 0) val -= good[i][j - c];
            if(i -r >=0 && j - c >= 0) val += good[i - r][j - c];
            if(val > 0) cout << hayStack[i][j];
            else cout << '.';
        }
        cout << "\n";
    }
}
// solves https://codeforces.com/gym/105446/problem/G
