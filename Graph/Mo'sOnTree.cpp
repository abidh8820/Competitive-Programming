#include "bits/stdc++.h"
using namespace std;

const int N = 1e6 + 7;
const int S = 450;

long long cur;
int  st[N], en[N],node[N];
vector<int> adj[N], preorder;

//preorder traversal
void dfs(int u, int p) {
    preorder.push_back(u);
    for (int v: adj[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    preorder.push_back(u);
}

// calculating starting and ending index in preorder
void pre() {
    int sz = preorder.size();
    for(int i=0; i<sz; i++)    en[preorder[i]] = i;
    for(int i=sz-1; i>=0; i--) st[preorder[i]] = i;
}

/*
 **For subtree queries :st[u] to en[u] for subtree of u
   
 ** For Path queries :
*/

void remove(int id) {
}

void add(int id) {
}


struct Query {
    int l, r, id;
    bool operator<(Query other) const {
        return make_pair(l / S, r) < make_pair(other.l / S, other.r);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // Euler Tour tree
    dfs(1,1),  pre();

    vector<Query> Q;
    // make queries

    sort(Q.begin(), Q.end());

    int l = 1, r = 0;
    long long ans = 0;

    for (int i = 0; i < n-1; i++) {
        while (l > Q[i].l) add(--l);
        while (r < Q[i].r) add(++r);
        while (l < Q[i].l) remove(l++);
        while (r > Q[i].r) remove(r--);
        // calculate ans
    }

}
