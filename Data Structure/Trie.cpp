#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 7;

struct Trie {
    static const int B = 31;
    struct node {
        node* nxt[2];
        int cnt;
        node() {
            nxt[0] = nxt[1] = NULL;
            cnt = 0;
        }
    } * root;

    Trie() { root = new node(); }

    void insert(int val) {
        node* cur = root;
        cur->cnt++;
        for (int i = B - 1; i >= 0; i--) {
            int b = val >> i & 1;
            if (cur->nxt[b] == NULL) cur->nxt[b] = new node();
            cur = cur->nxt[b];
            cur->cnt++;
        }
    }

    int XorMax(int x) {
        node* cur = root;
        int ans = 0;
        for (int i = B - 1; i >= 0; i--) {
            int k = x >> i & 1;
            if (cur->nxt[!k]) cur = cur->nxt[!k], ans <<= 1, ans++;
            else cur = cur->nxt[k], ans <<= 1;
        }
        return ans;
    }

    int XorMin(int x) {
        node* cur = root;
        int ans = 0;
        for (int i = B - 1; i >= 0; i--) {
            int k = x >> i & 1;
            if (cur->nxt[k]) cur = cur->nxt[k], ans <<= 1;
            else cur = cur->nxt[!k], ans <<= 1, ans++;
        }
        return ans;
    }

    void del(node* cur) {
        for (int i = 0; i < 2; i++)
            if (cur->nxt[i]) del(cur->nxt[i]);
        delete (cur);
    }
} 
