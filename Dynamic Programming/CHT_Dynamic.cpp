/*
 * Dynamic ConvexHull Trick - Maximizes f(x)
 * For minimization: insert(-m, -c) and negate the result
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const LL IS_QUERY = -(1LL << 62);

struct line {
    LL m, b;
    mutable function<const line *()> succ;

    bool operator<(const line &rhs) const {
        if (rhs.b != IS_QUERY) return m < rhs.m;
        const line *s = succ();
        if (!s) return 0;
        LL x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};

struct HullDynamic : public multiset<line> {
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end()) return y->m == x->m && y->b <= x->b;
        return 1.0 * (x->b - y->b) * (z->m - y->m) >=
               1.0 * (y->b - z->b) * (y->m - x->m);
    }

    void insert_line(LL m, LL b) {
        auto y = insert({m, b});
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) {
            erase(y);
            return;
        }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }

    LL eval(LL x) {
        auto l = *lower_bound((line){x, IS_QUERY});
        return l.m * x + l.b;
    }
};


//solves https://codeforces.com/contest/660/problem/F

const int N = 1e6 + 7;
LL a[N], p[N], s[N];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    int n;
    cin >> n;

    for(int i=1; i<=n; i++) cin >> a[i];
 
    for(int i=1; i<=n; i++){
        p[i] = a[i] + p[i-1];
        s[i] = i*a[i] + s[i-1];
    }

    HullDynamic hull;
    hull.insert_line(0,0);
 
    LL ans = 0;
    for(int i=1; i<=n; i++){
        ans = max(ans, hull.eval(p[i])+s[i]);
        hull.insert_line(-i,i*p[i] - s[i]);
    }
    cout << ans <<endl;
}
