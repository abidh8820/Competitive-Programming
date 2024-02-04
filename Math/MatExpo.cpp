#include <bits/stdc++.h>
using namespace std;

using LL = long long;
const int M = 1e9 + 7;

struct Matrix {
    int n, m;
    vector<vector<int>> mat;

    Matrix(int n = 0, int m = 0) : n(n), m(m) {
        mat.resize(n, vector<int>(m, 0));
    }

    void unity() {
        for (int i = 0; i < n; i++) mat[i][i] = 1;
    }

    Matrix operator*(const Matrix& b) const {
        Matrix ret(n, b.m);
        auto& ans = ret.mat;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < b.m; j++)
                for (int k = 0; k < m; k++)
                    ans[i][j] = (ans[i][j] + 1LL * mat[i][k] * b.mat[k][j]) % M;
        return ret;
    }
};

Matrix power(Matrix a, LL b) {
    Matrix ret(a.n, a.n);
    ret.unity();

    while (b) {
        if (b & 1) ret = ret * a;
        a = a * a;
        b >>= 1;
    }
    return ret;
}
