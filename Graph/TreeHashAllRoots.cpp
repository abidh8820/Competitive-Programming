/*
  O(N*log(N)*Log(N)) TreeHash for all roots
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 7;
vector<int> adj[N];
int cnt, Hash[N];

map<multiset<int>, int> ID; //key as the subtree
map<int, int> id;//key as root of the subtree

map<int, multiset<int>> subtree;

int dfs(int u, int p) {
    auto& sub = subtree[u];
    for (int v : adj[u]) {
        if (v == p) continue;
        sub.emplace(dfs(v, u));
    }
    if (!ID.count(sub)) ID[sub] = ++cnt;
    id[u] = ID[sub];
    return ID[sub];
}

void dfs2(int u, int p, int g) {
    auto& sub = subtree[u];
    if (u != 1) sub.emplace(g);

    if (!ID.count(sub)) ID[sub] = ++cnt;
    Hash[u] = ID[sub];

    for (int v : adj[u]) {
        if (v == p) continue;
        sub.erase(sub.find(id[v]));

        if (!ID.count(sub)) ID[sub] = ++cnt;
        dfs2(v, u, ID[sub]), sub.emplace(id[v]);
    }
}


//solves https://codeforces.com/problemset/problem/718/D

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cnt = 1;
    ID[multiset<int>()] = 1;
    dfs(1, 1), dfs2(1, 1, 1);

    set<int> st;
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() < 4) st.emplace(Hash[i]);
    }

    cout << st.size() << endl;
}
