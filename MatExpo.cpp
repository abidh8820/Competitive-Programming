#include "bits/stdc++.h"
using namespace std;

int N;
struct Mat {
    long long a[N+1][N+1];
    Mat operator*(const Mat& other) {
        Mat res;
        memset(res.a, 0, sizeof res.a);
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                for (int k = 1; k <= N; k++) {
                    res.a[i][k] = (res.a[i][k] + (a[i][j] * other.a[j][k]));
                }
        return res;
    }
};

Mat bm(Mat a, long long p) {
    if (p == 1) return a;
    if (p & 1) return a * (bm(a, p - 1));
    Mat tepm = bm(a, p / 2);
    return (tepm * tepm);
}

int main() {

}
