/*
* It could be a forest rather than a single tree. 
* The 'tree' holds the edges bridge trees' 
* 'ptr' = the number of new nodes in the bridge tree 
*/


#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 7;

vector<int> g[N], tree[N];
int in[N], low[N], ptr, compID[N];
int dist[N];

void go(int u, int par = -1) {
    in[u] = low[u] = ++ptr;
    for (int v : g[u]) {
        if (in[v]) {
            if (v == par)      par = -1;
            else low[u] = min(low[u], in[v]);
        } else {
            go(v, u);
            low[u] = min(low[u], low[v]);
        }
    }
}

void shrink(int u, int id) {
    compID[u] = id;
    for (int v : g[u])
        if (!compID[v]) {
            if (low[v] > in[u]) {
                tree[id].emplace_back(++ptr);
                tree[ptr].emplace_back(id);
                shrink(v, ptr);
            } else shrink(v, id);
        }
}


int main() {
    int n, m;
    cin >> n >> m;

    while (m--) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    for (int i = 1; i <= n; ++i)
        if (!in[i]) go(i);

    ptr = 0;
    for (int i = 1; i <= n; ++i) {
        if (!compID[i]) {
            shrink(i, ++ptr);
        }
    }
}

