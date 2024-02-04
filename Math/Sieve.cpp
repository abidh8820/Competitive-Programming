#include <bits/stdc++.h>
using namespace std;

using LL = long long;

const int N = 1e6 + 7;

int bpf[N];
vector<int> primes;

void sieve() {
    for (int i = 2; i < N; i++) {
        if (bpf[i] == 0) {
            primes.push_back(i);
            for (int j = i; j < N; j += i) bpf[j] = i;
        }
    }
}

vector<int> factorize(int x) {
    vector<int> fact;
    while (x > 1) {
        int p = bpf[x];
        while (x % p == 0) x /= p;
        fact.push_back(p);
    }
    return fact;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    sieve();
    for (int i = 0; i < 20; i++) cout << primes[i] << " ";
}

