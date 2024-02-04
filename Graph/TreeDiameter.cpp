#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 7;
vector<int> adj[N];
int n;

tuple<int, int, vector<int>> bfs(int node) {
    vector<int> dist(N, -1);
    vector<int> Q = {node};
    dist[node] = 0;

    for (int i = 0; i < Q.size(); i++) {
        int u = Q[i];
        for (int v : adj[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            Q.push_back(v);
        }
    }

    int last = node, mx = 0;
    for (int i = 1; i <= n; i++) {
        if (mx < dist[i]) {
            last = i;
            mx = dist[i];
        }
    }
    return make_tuple(mx, last, dist);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto [d1, x, v1] = bfs(1);
    auto [d2, u, v2] = bfs(x);
    auto [d3, v, v3] = bfs(u);

    for(int i=1; i<=n; i++) v2[i] = max(v2[i], v3[i]);
    vector<int> cnt(N, 0);
    for(int i=1; i<=n; i++) cnt[v2[i]]++;
  

    for(int i=1; i<n; i++) cout<<cnt[i-1]+1<<' ';
    cout << n <<endl;
}
