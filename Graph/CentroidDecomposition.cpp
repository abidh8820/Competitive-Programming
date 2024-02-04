//solves https://cses.fi/problemset/task/2080/
#include <bits/stdc++.h>
using namespace std;

using LL = long long;
const int N = 2e5 + 7;

int n, k;
vector<int> adj[N];
int sz[N];

LL ans = 0;
int cnt[N]{1}, mx_depth; // initilizes cnt[0] = 1
bool vis[N];

int dfs(int u, int p = 0) {
    sz[u] = 1;
    for (int i : adj[u])
        if (!vis[i] && i != p) sz[u] += dfs(i, u);
    return sz[u];
}

int centroid(int u, int p, int mx) {
    for (int v : adj[u])
        if (!vis[v] && v != p && sz[v] * 2 > mx) return centroid(v, u, mx);
    return u;
}

void go(int u, int p, int depth, bool filling) {
    if (depth > k) return;
    mx_depth = max(mx_depth, depth);

    if (filling) cnt[depth]++;
    else ans += cnt[k - depth];

    for (int v : adj[u])
        if (!vis[v] && v != p) go(v, u, depth + 1, filling);
}

void decompose(int u) {
    int mx = dfs(u, u);
    int c = centroid(u, u, mx);

    vis[c] = true, mx_depth = 0;

    for (int i : adj[c])
        if (!vis[i]) {
            go(i, c, 1, false);
            go(i, c, 1, true);
        }

    fill(cnt + 1, cnt + mx_depth + 1, 0);
    for (int v : adj[c]) if (!vis[v]) decompose(v);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    decompose(1);
    cout << ans;
}
