#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;

const int MX = 1e6 + 7, K = 20;
int lg[MX];
void pre() {
    lg[1] = 0;
    for (int i = 2; i < MX; i++) lg[i] = lg[i / 2] + 1;
}

struct RMQ {
    int N;
    VI v[K];
    RMQ(const VI &a) {
        N = a.size();
        v[0] = a;

        for (int k = 0; (1 << (k + 1)) <= N; k++) {
            v[k + 1].resize(N);
            for (int i = 0; i - 1 + (1 << (k + 1)) < N; i++) {
                v[k + 1][i] = gcd(v[k][i], v[k][i + (1 << k)]);
            }
        }
    }

    int findMin(int i, int j) {
        int k = lg[j - i + 1];
        return min(v[k][i], v[k][j + 1 - (1 << k)]);
    }
};

int main(){

    VI a = {1,2,3,4};

    RMQ rmq(a);

    cout<< rmq.findMin(1,2)<<endl;
}
