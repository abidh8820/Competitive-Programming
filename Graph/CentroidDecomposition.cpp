#include <bits/stdc++.h >
using namespace std;

const int N = 1e6 + 7, K = 22;
const int INF = 1e9 + 7;
vector<int> adj[N];

int sub[N];
bool vis[N];

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

void decompose(int u) {
    getsub(u, u);
    int c = centroid(u, u, sub[u] / 2);
    vis[c] = 1;
    for (int v : adj[c]) if (!vis[v]) decompose(v);
}

