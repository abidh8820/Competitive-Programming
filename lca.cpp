#include "bits/stdc++.h"
using namespace std;

const int N = 1e5 + 7;
vector<int> adj[N];
int depth[N], up[N][20];

void dfs(int u, int p) {
    for (auto v : adj[u]) {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        up[v][0] = u;

        for (int i = 1; i < 20; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }
        dfs(v, u);
    }
}


int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int k = depth[a] - depth[b];

    for (int j = 19; j >= 0; j--) {
        if (k & (1 << j))  a = up[a][j];
    }
    if (a == b)  return up[a][0];

    for (int j = 19; j >= 0; j--) {
        if (up[a][j] != up[b][j]) {
            a = up[a][j];  b = up[b][j];
        }
    }
    return up[a][0];
}

