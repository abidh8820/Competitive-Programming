#include "bits/stdc++.h"
using namespace std;
 
const int N = 1e6 + 7, K = 22;
vector<int> adj[N];
int depth[N], up[N][K];
 
void dfs(int u, int p) {
    for (auto v : adj[u]) {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        up[v][0] = u;
 
        for (int i = 1; i < K; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }
        dfs(v, u);
    }
}
 
 
int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int g = depth[a] - depth[b];
 
    for (int j = K-1; j >= 0; j--) {
        if (g & (1 << j))  a = up[a][j];
    }
    if (a == b)  return a;
 
    for (int j = K-1; j >= 0; j--) {
        if (up[a][j] != up[b][j]) {
            a = up[a][j];  b = up[b][j];
        }
    }
    return up[a][0];
}
