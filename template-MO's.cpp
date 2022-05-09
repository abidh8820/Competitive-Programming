#include "bits/stdc++.h"
using namespace std;

const int N = 1e6 + 7;
const int S = 450;

long long a[N], ans[N], cnt[N], sum;
// remove the index from current ans
void remove(int id) {
}

//add the index to the current ans
void add(int id) { 
}


struct Query {
    int l, r;
    bool operator<(Query other) const {
        return make_pair(l / S, r) < make_pair(other.l / S, other.r);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);


    int q;
    vector<Query> Q;
    //take queries and sort them

    int l = 1, r = 0;
    for (int i = 0; i < q; i++) {
        while (l > Q[i].l) add(--l);
        while (r < Q[i].r) add(++r);
        while (l < Q[i].l) remove(l++);
        while (r > Q[i].r) remove(r--);
    }

}
