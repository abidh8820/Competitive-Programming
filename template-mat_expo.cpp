#include "bits/stdc++.h"
using namespace std;

struct Mat {
    long long a[7][7];
    Mat operator*(const Mat& other) {
        Mat res;
        memset(res.a, 0, sizeof res.a);
        for (int i = 1; i <= 2; i++)
            for (int j = 1; j <= 2; j++)
                for (int k = 1; k <= 2; k++) {
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
