/*  -Wavelet Tree-
 *  INF : maximum value in the array
 *  valaues can be negetive asswell
 *  Use appropirate maximum & minimum value (INF, -INF)
 *  The array changes after applying init
 */

#include <bits/stdc++.h>
using namespace std;

const int N = (int)3e5 + 9;
const int INF = (int)1e9 + 9;

struct WaveletTree {
    int lo, hi;
    WaveletTree *l, *r;
    int *b, *c, bsz, csz;  // c holds the prefix sum of elements

    WaveletTree() { lo = 1, hi = 0, bsz = 0, csz = 0, l = NULL, r = NULL; }

    void init(int *from, int *to, int x, int y) {
        lo = x, hi = y;
        if (from >= to) return;

        int mid = (lo + hi) >> 1;
        auto f = [mid](int x) { return x <= mid; };
        b = (int *)malloc((to - from + 2) * sizeof(int));

        bsz = 0, b[bsz++] = 0;
        c = (int *)malloc((to - from + 2) * sizeof(int));

        csz = 0, c[csz++] = 0;
        for (auto it = from; it != to; it++) {
            b[bsz] = (b[bsz - 1] + f(*it));
            c[csz] = (c[csz - 1] + (*it));
            bsz++, csz++;
        }

        if (hi == lo) return;
        auto pivot = stable_partition(from, to, f);

        l = new WaveletTree();
        l->init(from, pivot, lo, mid);
        r = new WaveletTree();
        r->init(pivot, to, mid + 1, hi);
    }

    // kth smallest element in [l, r]
    // for array [1,2,1,3,5] 2nd smallest is 1 and 3rd smallest is 2
    int kth(int l, int r, int k) {
        if (l > r) return 0;
        if (lo == hi) return lo;
        int inLeft = b[r] - b[l - 1], lb = b[l - 1], rb = b[r];
        if (k <= inLeft) return this->l->kth(lb + 1, rb, k);
        return this->r->kth(l - lb, r - rb, k - inLeft);
    }

    // count of numbers in [l, r] Less than or equal to k
    int LTE(int l, int r, int k) {
        if (l > r || k < lo) return 0;
        if (hi <= k) return r - l + 1;
        int lb = b[l - 1], rb = b[r];
        return this->l->LTE(lb + 1, rb, k) + this->r->LTE(l - lb, r - rb, k);
    }

    // count of numbers in [l, r] equal to k
    int count(int l, int r, int k) {
        if (l > r || k < lo || k > hi) return 0;
        if (lo == hi) return r - l + 1;
        int lb = b[l - 1], rb = b[r];
        int mid = (lo + hi) >> 1;
        if (k <= mid) return this->l->count(lb + 1, rb, k);
        return this->r->count(l - lb, r - rb, k);
    }

    // sum of numbers in [l ,r] less than or equal to k
    int sum(int l, int r, int k) {
        if (l > r or k < lo) return 0;
        if (hi <= k) return c[r] - c[l - 1];
        int lb = b[l - 1], rb = b[r];
        return this->l->sum(lb + 1, rb, k) + this->r->sum(l - lb, r - rb, k);
    }

    ~WaveletTree() { delete l, delete r; }
};

int a[N];
WaveletTree Tree;

int main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) cin >> a[i];
    Tree.init(a + 1, a + n + 1, -INF, INF);
    // init() changes the array a[]

    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;

        cout << Tree.kth(l+1 , r , k + 1) << "\n";
    }

    return 0;
}
