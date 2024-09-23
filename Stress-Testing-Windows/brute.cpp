#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using PII = pair<int, int>;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while(t--){

        int n, m;
        cin >> n >> m;

        vector<string > s(n);
        for(int i = 0; i < n; i++){
            cin >> s[i];
        }

        set<char> goods = {'n', 'a', 'r', 'e', 'k'};
        map<char, int> mp;
        mp['n'] = 0, mp['a'] = 1, mp['r'] = 2, mp['e'] = 3, mp['k'] = 4;
      
        int best = 0;
        for(int mask = 1; mask < (1 << n); mask++){
            vector<string> g;
            int tot = 0;
            for(int j = 0; j < n; j++){
                if(mask >> j & 1) {
                    g.push_back(s[j]);
                for(int k = 0; k < m; k++) 
                    if(goods.count(s[j][k])) tot++;
                }
            }

            int cnt = 0, now = 0;
            for(auto ss : g){
                for(int j = 0; j < m; j++){
                    if(!goods.count(ss[j])) continue;
                    if(mp[ss[j]] == now) {
                        if(now == 4) cnt += 5;
                        now = (now + 1) % 5;
                    }
                }
            }
            int ans = 2 * cnt - tot;
            best = max(best, ans);
        }
        cout << best <<"\n";
    }
}


