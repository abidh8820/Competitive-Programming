// Range Minimum Query
#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 7;

struct SegTree {
    int n, a[N], tree[N << 1];

    int combine(int left, int right) { return min(left, right); }
    SegTree(int n_) { n = n_; }

    void init() {
        for (int i = 0; i < n; ++i) {
            tree[n + i] = a[i + 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    // assign a[p] = v
    void update(int p, int v) {
        for (p--, tree[p += n] = v; p > 1; p >>= 1) {
            tree[p >> 1] = combine(tree[p], tree[p ^ 1]);
        }
    }

    // range [l, r) sum
    int query(int l, int r) {
        int ret = INT_MAX;
        for (l--, l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ret = combine(ret, tree[l++]);
            if (r & 1) ret = combine(ret, tree[--r]);
        }
        return ret;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    SegTree tree(n);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        tree.update(i, x);
    }

    for (int i = 0; i < q; i++) {
        int X;
        cin >> X;
        if (X == 1) {
            int k, u;
            cin >> k >> u;
            tree.update(k, u);
        } else {
            int a, b;
            cin >> a >> b;
            cout << tree.query(a, b) << "\n";
        }
    }
}
