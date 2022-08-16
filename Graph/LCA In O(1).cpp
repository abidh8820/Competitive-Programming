/* LCA in O(1)
 * Preprocessing in NlongN
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int N = 1e6 + 7;
const int L = 21;

namespace LCA {

LL depth[N];
int st[N], en[N], LOG[N], par[N];
int a[N], id[N], table[L][N];

vector<PII> adj[N];
int n, root, Time, cur;

void init(int nodes, int root_) {
    n = nodes, root = root_, LOG[0] = LOG[1] = 0;
    for (int i = 2; i <= n; i++) LOG[i] = LOG[i >> 1] + 1;
    for (int i = 0; i <= n; i++) adj[i].clear();
}

void addEdge(int u, int v, int w) {
    adj[u].push_back(PII(v, w));
    adj[v].push_back(PII(u, w));
}

int lca(int u, int v) {
    if (en[u] > en[v]) swap(u, v);
    if (st[v] <= st[u] && en[u] <= en[v]) return v;

    int l = LOG[id[v] - id[u] + 1];
    int p1 = id[u], p2 = id[v] - (1 << l) + 1;
    int d1 = depth[table[l][p1]], d2 = depth[table[l][p2]];

    if (d1 < d2)   return par[table[l][p1]];
    else           return par[table[l][p2]];
}

LL dist(int u, int v) {
    int l = lca(u, v);
    return (depth[u] + depth[v] - (depth[l]*2));
}

/* Euler tour */
void dfs(int u, int p) {
    st[u] = ++Time, par[u] = p;

    for (auto [v, w] : adj[u]) {
        if (v == p) continue;
        depth[v] = depth[u] + w;
        dfs(v, u);
    }

    en[u] = ++Time;
    a[++cur] = u, id[u] = cur;
}

/* RMQ */
void pre() {
    cur = Time = 0,  dfs(root, root);
    for (int i = 1; i <= n; i++) table[0][i] = a[i];

    for (int l = 0; l < L - 1; l++) {
        for (int i = 1; i <= n; i++) {
            table[l + 1][i] = table[l][i];

            bool C1 = (1 << l) + i <= n;
            bool C2 = depth[table[l][i + (1 << l)]] < depth[table[l][i]];

            if (C1 && C2)   table[l + 1][i] = table[l][i + (1 << l)];
        }
    }
}

}
/* namespace LCA */

using namespace LCA;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    init(n, 1);
    for (int v = 2; v <= n; v++) {
        int u;
        cin >> u;
        addEdge(u, v, 1);
    }

    pre();
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << "\n";
    }
}
/* tesed on https://cses.fi/problemset/task/1688/ */
