#include "bits/stdc++.h"
using namespace std;

template <typename DT>
struct Segtree {
    vector<DT> tree, prob, a;

    Segtree(int n) {
        tree.resize(n * 4);
        prob.resize(n), a.resize(n);
    }

    void build(int u, int l, int r) {
        if (l == r) {
            tree[u] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(u * 2, l, mid);
        build(u * 2 + 1, mid + 1, r);
        tree[u] = min(tree[u * 2], tree[u * 2 + 1]);
    }

    void propagate(int u) {
        prob[u * 2] += prob[u];
        tree[u * 2] += prob[u];
        prob[u * 2 + 1] += prob[u];
        tree[u * 2 + 1] += prob[u];
        prob[u] = 0;
    }

    void update(int u, int l, int r, int i, int j, int val) {
        if (r < i || l > j) return;
        if (l >= i && r <= j) {
            prob[u] += val;
            tree[u] += val;
            return;
        }
        propagate(u);
        int mid = (l + r) / 2;
        update(u * 2, l, mid, i, j, val);
        update(u * 2 + 1, mid + 1, r, i, j, val);
        tree[u] = min(tree[u * 2], tree[u * 2 + 1]);
    }

    DT query(int u, int l, int r, int i, int j) {
        if (l > j || r < i) return 1e18;
        if (l >= i && r <= j) return tree[u];
        propagate(u);
        int mid = (l + r) / 2;
        return min(query(u * 2, l, mid, i, j), query(u * 2 + 1, mid + 1, r, i, j));
    }
}
