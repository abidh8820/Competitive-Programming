#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
const int N = 1e6 + 7;

vector<int> adj[N];

int depth[N], par[N];
int pos[N], val[N];

int head[N], heavy[N];
int cnt, tr[4 * N], lz[4*N];


int combine(int left, int right) { 
    return left + right;
}

void propagate(int u, int st, int en) {
    if (!lz[u]) return;
    tr[u] += (en - st + 1) * lz[u];
    if (st != en) {
        lz[2 * u] += lz[u];
        lz[2 * u + 1] += lz[u];
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
    if (r < st || en < l)        return 0;  
    else if (l <= st && en <= r) return tr[u];
    int mid = (st + en) / 2;
    return combine(query(2 * u, st, mid, l, r),  query(2 * u + 1, mid + 1, en, l, r));
}

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
        ret = max(ret, query(1, 1, cnt, pos[head[v]], pos[v]));
    }

    if (depth[u] > depth[v]) swap(u, v);
    if (u != v) ret = max(ret, query(1, 1, cnt, pos[u] + 1, pos[v]));
    return ret;
}

void update(int u, int v) {
    for(; head[u] != head[v]; v = par[head[v]]) {
        if(depth[head[u]] > depth[head[v]]) swap(u,v);
        update(1,1,cnt,pos[head[v]], pos[v],1);
    }
    if(depth[u] > depth[v]) swap(u,v);
    if(u != v) update(1, 1, cnt, pos[u]+1, pos[v],1);
}

void init(int root, int n) {
    for (int i = 1; i <= 4 * n; i++) {
        heavy[i] = -1, tr[i] = 0;
    }
    cnt = 0,  dfs(root, 0);
    decompose(root, root);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) adj[i].clear();

    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    init(1, n);


    while (m--) {
        char ch;
        int u, v;
        cin >> ch >> u >> v;
        if(ch=='P') update(u, v);
        else cout<<query(u,v)<<"\n";;
    }
}
