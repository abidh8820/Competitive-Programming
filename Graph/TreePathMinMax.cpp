#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;

const int N = 5e4 + 7, K = 20;

struct Tree {
    vector<PII> adj[N];

    int anc[N][K];
    int Min[N][K];
    int Max[N][K];
    int level[N];

    void add_edge(int u, int v, int w) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    void dfs(int u, int par, int W) {
        level[u] = level[par] + 1;
        anc[u][0] = par;
        Min[u][0] = Max[u][0] = W;
        for (int k = 1; k < K; k++) anc[u][k] = anc[anc[u][k - 1]][k - 1];
        for (int k = 1; k < K; k++) Min[u][k] = min(Min[u][k - 1], Min[anc[u][k - 1]][k - 1]);
        for (int k = 1; k < K; k++) Max[u][k] = max(Max[u][k - 1], Max[anc[u][k - 1]][k - 1]);

        for (auto [v, w] : adj[u]) {
            if (v == par) continue;
            dfs(v, u, w);
        }
    }

    int lca(int u, int v) {
        if (level[u] > level[v]) swap(u, v);
        for (int k = K - 1; k >= 0; k--)
            if (level[u] + (1 << k) <= level[v]) v = anc[v][k];

        if (u == v) return u;
        for (int k = K - 1; k >= 0; k--)
            if (anc[u][k] != anc[v][k]) u = anc[u][k], v = anc[v][k];
        return anc[u][0];
    }

    int findMax(int u, int v) {
        if (level[u] > level[v]) swap(u, v);
        int g = lca(u, v);

        int ret = 0;
        for (int k = K - 1; k >= 0; k--) {
            if (level[g] + (1 << k) <= level[u])
                ret = max(ret, Max[u][k]), u = anc[u][k];
            if (level[g] + (1 << k) <= level[v])
                ret = max(ret, Max[v][k]), v = anc[v][k];
        }
        return ret;
    }

    int getanc(int u, int d) {
        for (int k = 0; k < K; k++)
            if (d & (1 << k)) u = anc[u][k];
        return u;
    }

    int dist(int u, int v) {
        int g = lca(u, v);
        return level[u] + level[v] - 2 * level[g];
    }
};

