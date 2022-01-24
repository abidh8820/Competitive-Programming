#include "bits/stdc++.h"
using namespace std;


const int M = 1e9 + 7;
typedef long long LL;

int n, m, K;

struct Mat {
    bool a[55][55];
    Mat() { memset(a, 0, sizeof a);}

    Mat(int x) {
        memset(a, 0, sizeof a);
        for (int i = 1; i <= n; i++) a[i][i] = 1;
    }

    Mat operator*(const Mat& b) {
        Mat ret;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= n; k++) {
                    ret.a[i][k] = (ret.a[i][k] + (a[i][j] * b.a[j][k]));
                }
            }
        }
        return ret;
    }
};

Mat bm(Mat a, LL p) {
    if (p == 0) return Mat(1);
    if (p == 1) return a;
    if (p & 1) return a * bm(a, p - 1);
    Mat temp = bm(a, p / 2);
    return temp * temp;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    Mat dp;
    dp.a[0][0] = 1;dp.a[0][1] = 1;
    dp.a[1][0] = 1;dp.a[1][1] = 0;
    iden.a[0][0]=iden.a[1][1]=1;
    int n;
    cin >> n;
    Mat ans = bm(dp, n);
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            cout<<ans.a[i][j]<<' ';
        }
        cout<<endl;
    }

    cout<<ans.a[0][1]+ans.a[0][0]<<endl;
}
