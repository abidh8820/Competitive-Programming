#include "bits/stdc++.h"
using namespace std;

const int N = 1e6 + 7;

bool vis[N];
vector<int> order, component;

void dfs(int u, int tp = 0) {
    vis[u] = true;
    if (tp) component.push_back(v);
    for (int v : adj[u])
        if (!vis[v]) dfs(v, tp);
    if (!tp) order.push_back(v);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n, m;

    while (m--) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    for (int i = 1; i <= n; i++)
        if (!vis[i]) dfs(i);

    memset(vis, 0, sizeof vi);
    for (int i : order) {
        if (!vis[i]) dfs(i, 1);
        //got a new component
        component.clear();
    }

}

