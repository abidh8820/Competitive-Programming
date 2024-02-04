#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using PII = pair<int, int>;

struct SegTree {
    int n;
    vector<LL> tr, lz;

    SegTree(){};
    SegTree(int sz) {
        n = sz;
        tr.resize(4 * n, 0);
        lz.resize(4 * n, 0);
    }

    LL combine(LL left, LL right) { return left + right; }

    void propagate(int u, int st, int en) {
        if (!lz[u]) return;
        tr[u] += (en - st + 1) * lz[u];
        if (st != en) {
            lz[2 * u] += lz[u];
            lz[2 * u + 1] += lz[u];
        }
        lz[u] = 0;
    }

    void build(int u, int st, int en) {
        if (st == en) {
            tr[u] = a[st];
            lz[u] = 0;
            return;
        }
        int mid = (st + en) / 2;
        build(2 * u, st, mid);
        build(2 * u + 1, mid + 1, en);
        tr[u] = combine(tr[2 * u], tr[2 * u + 1]);
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

    LL query(int u, int st, int en, int l, int r) {
        propagate(u, st, en);
        if (r < st || en < l) return 0;
        if (l <= st && en <= r) return tr[u];
        int mid = (st + en) / 2;
        return combine(query(2 * u, st, mid, l, r), query(2 * u + 1, mid + 1, en, l, r));
    }

    void debug(int u, int st, int en) {
        cout << "--->" << u << " " << st << " " << en << " " << tr[u] << " "
             << lz[u] << endl;
        if (st == en) return;
        int mid = (st + en) / 2;
        debug(2 * u, st, mid);
        debug(2 * u + 1, mid + 1, en);
    }
};

