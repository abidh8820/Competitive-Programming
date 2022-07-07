#include "bits/stdc++.h"
using namespace std;

const int N = 1e6 + 7;
const int S = 450;


long long a[N], ans[N], cur;

void remove(int id) {
// remove index id from ans
}

void add(int id) {
// add index id to ans
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

    
    
    int q;
    cin >> q;
    
    vector<Query> Q(q);

    int cnt = 0;
    for(int i=0; i<q; i++) {
        cin >> Q[i].l>> Q[i].r;
        Q[i].l--;
        Q[i].id = i+1;
    }

    sort(Q.begin(), Q.end());

    int l = 1, r = 0;
    for (int i = 0; i < q; i++) {
        while (l > Q[i].l) add(--l);
        while (r < Q[i].r) add(++r);
        while (l < Q[i].l) remove(l++);
        while (r > Q[i].r) remove(r--);
        ans[Q[i].id] = cur;
    }
    for(int i=1; i<=q; i++) cout<<ans[i]<<endl;
}
