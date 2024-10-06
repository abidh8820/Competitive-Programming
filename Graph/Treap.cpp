// solves https://codeforces.com/contest/911/problem/G 
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    Node *l, *r;
    int key, prior;

    Node(int id) {
        l = r = nullptr;
        key = id;
        prior = rnd();
    }
};

struct Treap {
    Node *root;
    Treap() {
        root = nullptr;
    }

    void split(Node *treap, int pos, Node *&l, Node *&r) {
        if (treap == nullptr) {
            l = r = nullptr;
            return;
        }

        if (treap->key <= pos) {
            split(treap->r, pos, l, r);
            treap->r = l;
            l = treap;
        } 
        else {
            split(treap->l, pos, l, r);
            treap->l = r;
            r = treap;
        }
    }

    Node* merge(Node *l, Node *r) {
        if (!l || !r) return l ? l : r;
        if (l->prior < r->prior) {
            l->r = merge(l->r, r);
            return l;
        }
        r->l = merge(l, r->l);
        return r;
    }

    Node* merge_treap(Node *l, Node *r) {
        if(!l) return r;
        if(!r) return l;

        if(l->prior < r->prior) swap(l, r);
        Node *L, *R;

        split(r, l->key, L, R);
        l->r = merge_treap(l->r, R);
        l->l = merge_treap(L, l->l);
        return l;
    }

    void insert(int id) {
        Node *l, *r;
        split(root, id, l, r);
        root = merge(merge(l, new Node(id)), r);
    }

    Node* erase(int L, int R) {
        Node *l, *r, *mid, *mr;
        split(root, L - 1, l, r);
        split(r, R, mid, mr);
        root = merge(l, mr);
        return mid;
    }

    void combine(Node *x) { //combine with another Treap
        root = merge_treap(root, x);
    }

    vector<int> ans;
    void dfs(Node* cur) {
        if(!cur) return;
        dfs(cur -> l);
        ans.push_back(cur -> key);
        dfs(cur -> r);
    }


    vector<int> get() {
        ans.clear();
        dfs(root);
        return ans;
    }
} treap[N];

int ans[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        treap[k].insert(i);
    }

    int q;
    cin >> q;

    while(q--) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        Node *p = treap[x].erase(l, r);
        treap[y].combine(p);
    }

    for(int i = 1; i < N; i++) {
        auto p = treap[i].get();
        for(auto x : p) ans[x] = i;
    }

    for(int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];
    return 0;
}
