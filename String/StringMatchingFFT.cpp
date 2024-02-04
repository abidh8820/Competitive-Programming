#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
using PII = pair<LL, LL>;

#define double long double 

struct CD {
    double x, y;
    CD(double x = 0, double y = 0) : x(x), y(y) {}
    CD operator+(const CD &o) { return {x + o.x, y + o.y}; }
    CD operator-(const CD &o) { return {x - o.x, y - o.y}; }
    CD operator*(const CD &o) { return {x * o.x - y * o.y, x * o.y + o.x * y}; }
    void operator/=(double d) {
        x /= d;
        y /= d;
    }
    double real() { return x; }
    double imag() { return y; }
};
CD conj(const CD &c) { return CD(c.x, -c.y); }

const double PI = acos(-1.0L);

namespace FFT {
LL N;
vector<LL> perm;
vector<CD> wp[2];

void precalculate(LL n) {
    assert((n & (n - 1)) == 0), N = n;
    perm = vector<LL>(N, 0);
    for (LL k = 1; k < N; k <<= 1) {
        for (LL i = 0; i < k; i++) {
            perm[i] <<= 1;
            perm[i + k] = 1 + perm[i];
        }
    }
    wp[0] = wp[1] = vector<CD>(N);
    for (LL i = 0; i < N; i++) {
        wp[0][i] = CD(cos(2 * PI * i / N), sin(2 * PI * i / N));
        wp[1][i] = CD(cos(2 * PI * i / N), -sin(2 * PI * i / N));
    }
}

void fft(vector<CD> &v, bool invert = false) {
    if (v.size() != perm.size()) precalculate(v.size());
    for (LL i = 0; i < N; i++)
        if (i < perm[i]) swap(v[i], v[perm[i]]);
    for (LL len = 2; len <= N; len *= 2) {
        for (LL i = 0, d = N / len; i < N; i += len) {
            for (LL j = 0, idx = 0; j < len / 2; j++, idx += d) {
                CD x = v[i + j];
                CD y = wp[invert][idx] * v[i + j + len / 2];
                v[i + j] = x + y;
                v[i + j + len / 2] = x - y;
            }
        }
    }
    if (invert) {
        for (LL i = 0; i < N; i++) v[i] /= N;
    }
}

void pairfft(vector<CD> &a, vector<CD> &b, bool invert = false) {
    LL N = a.size();
    vector<CD> p(N);
    for (LL i = 0; i < N; i++) p[i] = a[i] + b[i] * CD(0, 1);
    fft(p, invert);
    p.push_back(p[0]);

    for (LL i = 0; i < N; i++) {
        if (invert) {
            a[i] = CD(p[i].real(), 0);
            b[i] = CD(p[i].imag(), 0);
        } else {
            a[i] = (p[i] + conj(p[N - i])) * CD(0.5, 0);
            b[i] = (p[i] - conj(p[N - i])) * CD(0, -0.5);
        }
    }
}

vector<LL> multiply(const vector<LL> &a, const vector<LL> &b) {
    LL n = 1;
    while (n < a.size() + b.size()) n <<= 1;

    vector<CD> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n);
    fb.resize(n);

    //        fft(fa); fft(fb);
    pairfft(fa, fb);
    for (LL i = 0; i < n; i++) fa[i] = fa[i] * fb[i];
    fft(fa, true);

    vector<LL> ans(n);
    for (LL i = 0; i < n; i++) ans[i] = round(fa[i].real());
    return ans;
}
}  

// find occurrences of t in s where '?'s are automatically matched with any
// character res[i + m - 1] = sum_j=0 to m - 1_{s[i + j] * t[j] * (s[i + j] - t[j])^2

vector<LL> findMatches(vector<LL> &s, vector<LL> &t) {
    LL n = s.size(), m = t.size();
    vector<LL> s1(n), s2(n), s3(n);

    // for string assign any non zero number for non '?'s
    for (LL i = 0; i < n; i++) s1[i] = s[i];

    for (LL i = 0; i < n; i++) s2[i] = s1[i] * s1[i];
    for (LL i = 0; i < n; i++) s3[i] = s1[i] * s2[i];

    vector<LL> t1(m), t2(m), t3(m);

    // for string assign any non zero number for non '?'s
    for (LL i = 0; i < m; i++) t1[i] = t[i];
    for (LL i = 0; i < m; i++) t2[i] = t1[i] * t1[i];
    for (LL i = 0; i < m; i++) t3[i] = t1[i] * t2[i];

    reverse(t1.begin(), t1.end());
    reverse(t2.begin(), t2.end());
    reverse(t3.begin(), t3.end());

    vector<LL> s1t3 = FFT::multiply(s1, t3);
    vector<LL> s2t2 = FFT::multiply(s2, t2);
    vector<LL> s3t1 = FFT::multiply(s3, t1);

    vector<LL> res(n);
    for (LL i = 0; i < n; i++) res[i] = s1t3[i] - s2t2[i] * 2 + s3t1[i];

    vector<LL> oc;
    for (LL i = m - 1; i < n; i++)
        if (res[i] == 0) oc.push_back(i - m + 1);
    return oc;
}


//solves https://codeforces.com/gym/104288/problem/G
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    LL r, c;
    cin >> r >> c;

    vector<vector<LL>> a(r, vector<LL>(c));

    for (LL i = 0; i < r; i++) {
        for (LL j = 0; j < c; j++) {
            cin >> a[i][j];
        }
    }

    LL n, m;
    cin >> n >> m;

    vector<LL> s;
    for (LL i = 0, x; i < n * m; i++) {
        cin >> x;
        s.push_back(x);
    }

    vector<LL> t;
    for (LL i = 0; i < r; i++) {
        for (LL j = 0; j < c; j++) {
            t.push_back(a[i][j]);
        }
        while (i<r-1 && t.size() % m != 0) t.push_back(0);
    }


    auto ans = findMatches(s, t);
    LL cnt = 0;

    map<LL, PII> idx;
    for (LL i = 1; i <= n; i++) {
        for (LL j = 1; j <= m; j++) {
            idx[cnt++] = PII(i, j);
        }
    }

    vector<PII> res;
    for (LL x : ans) 
        if(idx[x].first + r - 1 <= n and idx[x].second + c - 1 <= m) res.push_back(idx[x]);

    sort(res.begin(), res.end());
    cout << res.size()<<endl;
    for (auto [x, y] : res) cout << x << " " << y << "\n";
}
