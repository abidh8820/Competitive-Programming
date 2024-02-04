/*
 * Find kth shortest path 
 * using Dijkstra's Algo
 * Replace k = 1 to find the shortest path
 * cnt[u] = number of times u is visited
*/

#include "bits/stdc++.h"
using namespace std;

const int N = 1e6 + 7;
typedef long long LL;

typedef pair<LL,LL> PII;
vector<PII> adj[N];


int cnt[N]; 

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    priority_queue<PII, vector<PII>, greater<PII>> Q;
    Q.push({0, 1});

    while (!Q.empty()) {
        auto [d, u] = Q.top();
        Q.pop(), cnt[u]++;

        if (u == n && cnt[u]==k) {
            cout << d << endl;
            return 0;
        }

        if (cnt[u] <= k) {
            for (auto [v, w] : adj[u]) {
                Q.push({d + w, v});
            }
        }
    }
}

//https://cses.fi/problemset/task/1196/
