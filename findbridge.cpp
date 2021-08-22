
const int N = 1e5 + 7;
int dt[N], low[N], Time;
vector<int> adj[N];

void findbriges(int u, int p) {
    low[u] = dt[u] = ++Time;
    for (auto v : adj[u]) {
        if (v == p) continue;
        if (dt[v]) low[u] = min(low[u], dt[v]);
        else {
            findbriges(v, u);
            if (dt[u] < low[v]) bridges.push_back(pii(u, v));
            low[u] = min(low[u], low[v]);
        }
    }
}
