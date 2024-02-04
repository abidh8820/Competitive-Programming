#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
const int N = 5e5 + 7;

vector<int> adj[N];

int depth[N], par[N];
int pos[N], val[N];

int head[N], heavy[N];
int cnt;

int combine(int left, int right) { return max(left, right); }

struct SegTree {
    int n;
    vector<int> tr, lz;

    SegTree(){};
    SegTree(int sz) {
        n = sz;
        tr.resize(4 * n, 0);
        lz.resize(4 * n, 0);
    }

    void propagate(int u, int st, int en) {
        if (!lz[u]) return;
        tr[u] = lz[u];
        if (st != en) {
            lz[2 * u] = lz[u];
            lz[2 * u + 1] = lz[u];
        }
        lz[u] = 0;
    }
    void update(int u, int st, int en, int l, int r, int x) {
        propagate(u, st, en);
        if (r < st || en < l) return;

        if (l <= st && en <= r) {
            lz[u] += x;
            propagate(u, st, en);
            return;
        }

        int mid = (st + en) / 2;
        update(2 * u, st, mid, l, r, x);
        update(2 * u + 1, mid + 1, en, l, r, x);
        tr[u] = combine(tr[2 * u], tr[2 * u + 1]);
    }

    int query(int u, int st, int en, int l, int r) {
        propagate(u, st, en);
        if (r < st || en < l) return 0;
        if (l <= st && en <= r) return tr[u];
        int mid = (st + en) / 2;
        return combine(query(2 * u, st, mid, l, r), query(2 * u + 1, mid + 1, en, l, r));
    }
} tree;

int dfs(int u, int p) {
    int sz = 1, mxsz = 0;
    depth[u] = depth[p] + 1;

    for (int v : adj[u]) {
        if (v == p) continue;
        par[v] = u;
        int subsz = dfs(v, u);
        if (subsz > mxsz) heavy[u] = v, mxsz = subsz;
        sz += subsz;
    }
    return sz;
}

void decompose(int u, int h) {
    head[u] = h, pos[u] = ++cnt;
    if (heavy[u] != -1) decompose(heavy[u], h);

    for (int v : adj[u]) {
        if (v == par[u]) continue;
        if (heavy[u] != v) decompose(v, v);
    }
}

int query(int u, int v) {
    int ret = 0;
    for (; head[u] != head[v]; v = par[head[v]]) {
        if (depth[head[u]] > depth[head[v]]) swap(u, v);
        ret = max(ret, tree.query(1, 1, cnt, pos[head[v]], pos[v]));
    }

    if (depth[u] > depth[v]) swap(u, v);

    // for edge query
    // if (u != v) ret = combine(ret, query(1, 1, cnt, pos[u] + 1, pos[v]));
    // for node query
    ret = combine(ret, tree.query(1, 1, cnt, pos[u], pos[v]));
    return ret;
}

void update(int u, int v, int x) {
    for (; head[u] != head[v]; v = par[head[v]]) {
        if (depth[head[u]] > depth[head[v]]) swap(u, v);
        tree.update(1, 1, cnt, pos[head[v]], pos[v], x);
    }
    if (depth[u] > depth[v]) swap(u, v);

    /*update on edge
      if (u != v) update(1, 1, cnt, pos[u] + 1, pos[v], x); */

    // update on node
    tree.update(1, 1, cnt, pos[u], pos[v], x);
}

void init(int root, int n) {
    for (int i = 1; i <= n; i++) heavy[i] = -1;
    cnt = 0, dfs(root, 0);
    decompose(root, root);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) adj[i].clear();
    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    init(1, n);// decomsing tree
    tree = SegTree(n);
    for (int i = 1; i <= n; i++) update(i, i, val[i]);

    while (m--) {
        int tp;
        cin >> tp;

        if (tp == 1) {
            int s, x;
            cin >> s >> x;
            update(s, s, x);
        } else {
            int u, v;
            cin >> u >> v;
            cout << query(u, v) << " ";
        }
    }
}
