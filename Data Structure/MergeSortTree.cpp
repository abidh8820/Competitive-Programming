/* 
 * Merge Sort Tree
 * Build in O(nlong)
 * Finding number of elements in a range <= val in O(log^2n)
 * finding the kth value in a range in O(log^3n)
*/  

#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 7;
typedef vector<int> VI;

int a[N];
vector<int> tr[N * 4];

VI merge(VI &a, VI &b) {
    int i, j;
    VI ret;
    for (i = 0, j = 0; i < a.size() && j < b.size();) {
        if (a[i] < b[j]) ret.push_back(a[i++]);
        else             ret.push_back(b[j++]);
    }
    while (i < a.size()) ret.push_back(a[i++]);
    while (j < b.size()) ret.push_back(b[j++]);
    return ret;
}

void build(int u, int st, int en) {
    if (st == en) {
        tr[u].push_back(a[en]);
        return;
    }

    int mid = (st + en) / 2;
    build(u * 2, st, mid);
    build(2 * u + 1, mid + 1, en);
    tr[u] = merge(tr[2 * u], tr[2 * u + 1]);
}

//number of elements in the range that is <= val
int query(int u, int st, int en, int l, int r, int val) {
    if (l > en || r < st) return 0;
    if (l <= st && en <= r) {
        return lower_bound(tr[u].begin(), tr[u].end(), val + 1) - tr[u].begin();
    }
    int mid = (en + st) / 2;
    return query(2*u, st, mid, l, r, val) + query(2*u+1, mid + 1, en, l, r, val);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) cin >> a[i];


    build(1, 1, n);

    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;

        int lo = -1e9, hi = 1e9 + 5, ans;
        // kth element in the range [l,r]
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (query(1, 1, n, l, r, mid) < k) lo = mid + 1;
            else    ans = mid, hi = mid - 1;
        }
        cout << ans << endl;
    }
}
