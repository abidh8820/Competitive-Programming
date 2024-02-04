#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using PII = pair<int, int>;

const int N = 1e5 + 7;

int tin[N], low[N], timer;
bool vis[N], is_cut[N];

vector<int> adj[N];

void dfs(int v, int p = -1) {
    vis[v] = true;
    tin[v] = low[v] = timer++;

    int children = 0;

    for (int to : adj[v]) {
        if (to == p) continue;
        if (vis[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p != -1) is_cut[v] = true;
            ++children;
        }
    }
    if (p == -1 && children > 1) is_cut[v] = true;
}

void find_cutpoints(int n) {
    timer = 0;
    for (int i = 0; i <= n; i++) {
        vis[i] = is_cut[i] = false;
        tin[i] = low[i] == -1;
    }

    for (int i = 0; i < n; ++i) {
        if (!vis[i]) dfs(i);
    }
}


//solves https://lightoj.com/problem/ant-hills
int main() {
    int t, cs = 0;

    cin >> t;
    while (t--) {
        cout << "Case " << ++cs << ": ";

        int n, m;
        cin >> n >> m;

        for (int i = 0; i <= n; i++) {
            adj[i].clear();
        }

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        find_cutpoints(n);
        int ans = 0;
        for (int i = 1; i <= n; i++) ans += is_cut[i];

        cout << ans << "\n";
    }
}

