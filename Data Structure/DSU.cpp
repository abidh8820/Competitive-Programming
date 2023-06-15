#include "bits/stdc++.h"
using namespace std;

const int N = 1e5 + 7;

struct DSU {
    vector<int> par;

    DSU(){};

    DSU(int n) {
        par.resize(n + 2);
        iota(par.begin(), par.end(), 0);
    }

    int find(int u) {
        if (u == par[u]) return u;
        return par[u] = find(par[u]);
    }
    void merge(int u, int v) { par[find(u)] = find(v); }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
}

