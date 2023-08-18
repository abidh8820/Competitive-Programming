#include <bits/stdc++.h >
using namespace std;

const int N = 1e6 + 7, K = 22;
const int INF = 1e9 + 7;
vector<int> adj[N];

int sub[N], par[N];
bool vis[N];

int anc[N][K];
int level[N];
int ans[N];

void dfs(int u, int p) {
    level[u] = level[p] + 1;
    anc[u][0] = p;
    for (int k = 1; k < K; k++) anc[u][k] = anc[anc[u][k - 1]][k - 1];

    for (int v : adj[u])
        if (v ^ p) dfs(v, u);
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

int getanc(int u, int d) {
    for (int k = 0; k < K; k++)
        if (d & (1 << k)) u = anc[u][k];
    return u;
}

int dist(int u, int v) {
    int g = lca(u, v);
    return level[u] + level[v] - 2 * level[g];
}

void getsub(int u, int p) {
    sub[u] = 1;
    for (int v : adj[u])
        if (!vis[v] && v ^ p) getsub(v, u), sub[u] += sub[v];
}

int centroid(int u, int p, int r) {
    for (int v : adj[u])
        if (!vis[v] && v ^ p)
            if (sub[v] > r) return centroid(v, u, r);
    return u;
}

void decompose(int u, int p) {
    getsub(u, u);
    int c = centroid(u, u, sub[u] / 2);
    vis[c] = 1, par[c] = p;
    for (int v : adj[c])
        if (!vis[v]) decompose(v, c);
}

// update ans for all ancin the centroid tree
void update(int u) {
    for (int v = u; v > 0; v = par[v]) {
        ans[v] = min(ans[v], dist(v, u));
    }
}

//query through all the anc in the centroid tree
int query(int u) {
    int ret = INF;
    for (int v = u; v > 0; v = par[v]) {
        ret = min(ret, ans[v] + dist(u, v));
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);
    decompose(1, 0);

    for (int i = 1; i <= n; i++) ans[i] = INF;
    update(1);

    while (m--) {
        int tp, u;
        cin >> tp >> u;

        if (tp == 1) update(u);
        else cout << query(u) << "\n";
    }
}

