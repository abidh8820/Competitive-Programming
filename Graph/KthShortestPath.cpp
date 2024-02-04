/* K-th Shortest path using dijkstra*/
/* solves https://lightoj.com/problem/not-the-best */

#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using PII = pair<LL, LL>;

const LL N = 5e3 + 7;
const LL INF = 1e9 + 7;

vector<PII> adj[N];

int main() {
    LL t, cs = 0;

    cin >> t;
    while (t--) {
        cout << "Case " << ++cs << ": ";

        int n, m, k;
        cin >> n >> m;
        k = 2;

        for (int i = 1; i <= n; i++) {
            adj[i].clear();
        }

        for (LL i = 1; i <= m; i++) {
            LL u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        priority_queue<PII, vector<PII>, greater<PII>> Q;
        vector<vector<LL>> dist(n + 1, vector<LL>(k + 1));
        vector<LL> vis(n + 1);

        Q.push({0, 1});

        while (!Q.empty()) {
            auto [d, u] = Q.top();
            Q.pop();
            if (vis[u] >= k) continue;

            // if kth and (k-1)th path need to be of different value
            if (vis[u] && dist[u][vis[u]] == d) continue;

            vis[u]++, dist[u][vis[u]] = d;
            for (auto [v, w] : adj[u])
                if (vis[v] < k) Q.push(PII(w + d, v));
        }

        cout << dist[n][k] << "\n";
    }
}


