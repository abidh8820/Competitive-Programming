#include <bits/stdc++.h>
using namespace std;

const int N = 5e6 + 1;

int phi[N];
bool composite[N];

void totient() {
    phi[1] = 1; vector<int> primes;
    for (int i = 2; i < N; i++) {
        if (!composite[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (int p : primes) {
            if (p * i > N) break;
            composite[i * p] = true;

            if (i % p == 0) {
                phi[i * p] = phi[i] * p; break;
            } 
            else  phi[i * p] = phi[i] * phi[p];
        }
    }
}

