#include "bits/stdc++.h"
using namespace std;

const int M = 1e9 + 7;

struct Mat {
    int a[2][2]={{0,0},{0,0}};
    Mat operator *(const Mat& other) {
        Mat res;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++) {
                    res.a[i][k] = (res.a[i][k] + a[i][j]* other.a[j][k]) % M;
                }
        return res;
    }
};

Mat iden;

Mat bm(Mat a, int p) {
    if(p==0)return iden;
    if (p == 1) return a;
    if (p & 1) return a * (bm(a, p - 1));
    Mat tepm = bm(a, p / 2);
    return (tepm * tepm);
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
