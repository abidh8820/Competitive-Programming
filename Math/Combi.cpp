#include <bits/stdc++.h>

typedef long long LL;

const int N = 1e6 + 7;


struct  MODSPACE {

const int M = 1e9 + 7;
LL fac[N], invfac[N];

LL BM(LL a, LL p) {
	if (p == 0) return 1;
	if (p == 1) return a;
	if (p & 1) return (a * BM(a, p - 1)) % M;
	LL f = BM(a, p / 2);
	return (f * f) % M;
}

void pre() {
	fac[0] = 1;
	for (int i = 1; i < N; i++) fac[i] = (fac[i - 1] * i) % M;
	invfac[N - 1] = BM(fac[N - 1], M - 2);
	for (int i = N - 2; i >= 0; i--) invfac[i] = (invfac[i + 1] * (i + 1)) % M;
}
 

int main(){

}
