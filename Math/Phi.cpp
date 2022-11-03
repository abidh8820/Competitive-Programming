#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 7;

long long phi[N];

void sieve() {
    for (int i = 0; i < N; i++) phi[i] = i;
    for (int i = 2; i < N; i++) {
        if (phi[i] != i) continue;
        for (int j = i; j < N; j += i) phi[j] -= phi[j] / i;
    }
}
