/* Bellman-Ford For detecting and
 * printing negetive cycle
 */

#include "bits/stdc++.h"
using namespace std;

const int N = 3e3 + 7;
long long dist[N], par[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < N; i++) {
        dist[i] = 1e18;
        par[i] = -1;
    }

    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> edges;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
    }

    int last;
    dist[1] = 0;

    for (int i = 0; i < n; i++) {
        last = -1;
        for (auto [u, v, w] : edges) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                par[v] = u, last = v;
            }
        }
    }

    /*if last == -1 no negetive cycle found */

    if (last == -1) {
        cout << "NO" << endl;
    } else {
        for (int i = 0; i < n; i++) last = par[last];
        cout << "YES" << endl;

        vector<int> cycle;
        for (int cur = last;; cur = par[cur]) {
            cycle.push_back(cur);
            if (cur == last && cycle.size() > 1) break;
        }

        reverse(cycle.begin(), cycle.end());
        for (int i : cycle) cout << i << ' ';
        cout << endl;
    }
}

