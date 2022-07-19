#include <bits/stdc++.h>
using namespace std;


typedef long long LL;
const int N = 1 << 18;

LL tree[N * 4], lazy[N * 4], a[N];

LL combine(LL u, LL v){
    return u + v;
}

void build(int u, int l, int r) {
    lazy[u] = 0;
    if (l == r) {
        tree[u] = a[l];  return;
    }
    int mid = (l + r) / 2;
    build(u * 2, l, mid);
    build(u * 2 + 1, mid + 1, r);
    tree[u] = min(tree[u * 2], tree[u * 2 + 1]);
}

//for max, min query just add lazy * 1;
void propagate(int u,int l, int r) {
    int mid = (l+r)/2;
    lazy[u * 2] += lazy[u];
    tree[u * 2] += lazy[u]*(mid-l+1);   
    lazy[u * 2 + 1] += lazy[u];
    tree[u * 2 + 1] += lazy[u]*(r-mid);
    lazy[u] = 0;
}

void update(int u, int l, int r, int i, int j, int val) {
    if (r < i || l > j) return;
    if (l >= i && r <= j) {
        // for max, min query just add lazy * 1;
        lazy[u] += val; tree[u] += val*(r-l+1);  return;
    }

    propagate(u,l,r);int mid = (l + r) / 2;
    update(u * 2, l, mid, i, j, val);
    update(u * 2 + 1, mid + 1, r, i, j, val);
    tree[u] = combine(tree[u * 2], tree[u * 2 + 1]);
}

LL query(int u, int l, int r, int i, int j) {
    if (l > j || r < i) return 0;
    if (l >= i && r <= j) return tree[u];
    propagate(u,l,r);   int mid = (l + r) / 2;
    return combine(query(u * 2, l, mid, i, j), query(u * 2 + 1, mid + 1, r, i, j));
} 


