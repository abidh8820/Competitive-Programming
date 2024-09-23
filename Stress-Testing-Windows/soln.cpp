
#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using PII = pair<int, int>;

const int N = 1e3 + 5;
int dp[N][5];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while(t--){
        int n, m;
        cin >> n >> m;

        vector<string> s(n + 1);
        for(int i = 1 ; i <= n; i++) cin >> s[i];

        for(int i = 0; i <= n; i++) 
            for(int j = 0; j < 5; j++) dp[i][j] = -1e9;

        map<char, int> mp;
        mp['n'] = 0, mp['a'] = 1, mp['r'] = 2, mp['e'] = 3, mp['k'] = 4;
        dp[0][4] = 0;

        int best = 0;
        set<char> goods = {'n', 'a', 'r', 'e', 'k'};
        for(int i = 1; i <= n; i++){
            for(int prev = 0; prev < 5; prev++){

                int nxt = (prev + 1) % 5;
                int score = -1e9, cur = 0, id = -1;

                set<int> ids;
                for(int j = 0; j < m; j++){
                    if(!goods.count(s[i][j])) continue;
                    if(mp[s[i][j]] == nxt && nxt == 4) nxt = (nxt + 1) % 5, cur += 5, id = j;
                    else if(mp[s[i][j]] == nxt) nxt = (nxt + 1) % 5;
                    else if(goods.count(s[i][j])) cur--, ids.emplace(j);
                }

                dp[i][(nxt + 4) % 5] = max(dp[i][(nxt + 4) % 5], dp[i - 1][prev] + cur);
                dp[i][prev] = max(dp[i][prev], dp[i - 1][prev]);
                score = dp[i - 1][prev] + cur;

                for(int j = id + 1; j < m; j++){
                    if(!goods.count(s[i][j])) continue;
                    if(!ids.count(j)) score--;
                }
                best = max(best, score);
            }
        }

        cout << best <<"\n";
    }        
}


