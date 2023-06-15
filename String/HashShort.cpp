#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL, LL> PLL;


const PLL M = {1e9 + 7, 1e9 + 9};
const PLL base = {1009, 1007};
const int N = 1e6 + 7;

PLL operator+(const PLL& a, LL x) { return {a.first + x, a.second + x}; }
PLL operator*(const PLL& a, LL x) { return {a.first * x, a.second * x}; }
PLL operator+(const PLL& a, PLL x) { return {a.first + x.first, a.second + x.second}; }
PLL operator-(const PLL& a, PLL x) { return {a.first - x.first, a.second - x.second}; }
PLL operator*(const PLL& a, PLL x) { return {a.first * x.first, a.second * x.second}; }
PLL operator%(const PLL& a, PLL m) { return {a.first % m.first, a.second % m.second}; }

PLL pb[N];

void hashPre() {
    pb[0] = {1, 1};
    for (int i = 1; i < N; i++) pb[i] = (pb[i - 1] * base) % M;
}

/// Calculates hashes of all prefixes of s including empty prefix
vector<PLL> hashList(string s) {
    int n = s.size();
    vector<PLL> ans(n + 1);
    ans[0] = {0, 0};
    for (int i = 1; i <= n; i++) ans[i] = (ans[i - 1] * base + s[i - 1]) % M;
    return ans;
}

/// Calculates hash of substring s[l..r] (1 indexed)
PLL substringHash(const vector<PLL>& hashlist, int l, int r) {
    return (hashlist[r] + (M - hashlist[l - 1]) * pb[r - l + 1]) % M;
}

/// Calculates Hash of a string
PLL Hash(string s) {
    PLL ans = {0, 0};
    for (int i = 0; i < s.size(); i++) ans = (ans * base + s[i]) % M;
    return ans;
}
