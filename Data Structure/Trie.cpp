#include <bits/stdc++.h>
using namespace std;

struct node {
    node* next[2] = {NULL, NULL};
    int cnt = 0;
} * root;

void insert(int x, int del) {
    auto cur = root;
    for (int i = 31; i >= 0; i--) {
        int bit = (x >> i) & 1;
        if (cur->next[bit] == NULL) cur->next[bit] = new node();
    }
}


