#include "bits/stdc++.h"
using namespace std;

using LL = long long;
using PII = pair<int,int>;
const LL N = 1e6 + 7;

bool vis[N];

vector<int> adj[N], adjr[N], g[N];
//g is the condensed graph

vector<int> order, component;
vector<PII> edges;

// tp = 0 ,finding topo order
// tp = 1 , reverse edge traversal

void dfs(int u, int tp = 0) {
    vis[u] = true;
    if (tp) component.push_back(u);
    auto& ad = (tp ? adjr : adj);
    for (int v : ad[u])
        if (!vis[v]) dfs(v, tp);
    if (!tp) order.push_back(u);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    while (m--) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adjr[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs(i);
    }

    memset(vis, 0, sizeof vis);
    reverse(order.begin(), order.end());

    vector<LL> ID(n + 1);

    LL ptr = 0;
    for (LL i : order) {
        if (!vis[i]) {
            dfs(i, 1);
            ptr++;
            for (LL u : component) ID[u] = ptr;
            sz[ptr] = component.size();
            component.clear();
        }
    }

    for (auto [u, v] : edges) {
        if (!cand[u] or !cand[v]) continue;
        if (ID[u] == ID[v]) continue;
        g[ID[u]].push_back(ID[v]);
    }
}

