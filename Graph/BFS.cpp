#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using PII = pair<int, int>;

const int N = 1e6 + 7;
const int INF = 1e9 + 7;

int n, m;
vector<int> adj[N];

vector<int> bfs(int s) {
    vector<int> d(n, INF);
    d[s] = 0;
    vector<int> Q = {s};

    for (int i = 0; i < Q.size(); i++) {
        int u = Q[i];
        for (int v : adj[u]) {
            if (d[v] > d[u] + 1) {
                d[v] = d[u] + 1;
                Q.push_back(v);
            }
        }
    }

    return d;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t, cs = 0;
    cin >> t;

    while (t--) {
        cout << "Case " << ++cs << ": ";
        cin >> n >> m;

        for (int i = 0; i < n; i++) adj[i].clear();

        for (int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int source, sink;
        cin >> source >> sink;

        auto d1 = bfs(source);
        auto d2 = bfs(sink);

        int ans = 0;
        for (int i = 0; i < n; i++) 
            ans = max(ans, d1[i] + d2[i]);

        cout << ans << "\n";
    }
}

