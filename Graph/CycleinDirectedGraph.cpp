#include "bits/stdc++.h"
using namespace std;

const int N = 1e6 + 7;
vector<int> adj[N];
int par[N], vis[N], st, en;

void dfs(int u, int p = 0) {
    if (st) return;
    for (int v : adj[u]) {
        if (vis[v] == 0) {
            par[v] = u,
            vis[v] = true;
            dfs(v, u);
            if (st) return;
        } 
        else if (vis[v] == 1) {
            st = v, en = u;
            return;
        }
    }
    vis[u] = 2;  // marked as a visied component
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    for (int i = 1; i <= n; i++) {
        if (st) break;
        if (vis[i] == 1) continue;
        vis[i] = true;
        dfs(i);
    }

    int cur = en;
    vector<int> ans;
    while (cur) {
        ans.push_back(cur);
        if (cur == st) break;
        cur = par[cur];
    }

    if (ans.empty()) cout<<"NO cycle detected"<<endl;
    else {
        ans.push_back(ans[0]);
        cout << ans.size() << endl;
        reverse(ans.begin(), ans.end());
        for (int i : ans) cout << i << ' ';
        cout << endl;
    }
}
