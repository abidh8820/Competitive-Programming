#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 7;
vector<int> adj[N];

map<vector<int>, int> ID;
int cnt;

int dfs(int u, int p) {
    vector<int> sub;
    for (int v : adj[u]) {
        if (v == p) continue;
        sub.emplace_back(dfs(v, u));
    }
    sort(sub.begin(), sub.end());
    if (!ID.count(sub)) ID[sub] = ++cnt;
    return ID[sub];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cnt = 1;
    ID[vector<int>(0)] = cnt;
    int hash = dfs(1, 1);
}
