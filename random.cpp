#include <bits/stdc++.h>
using namespace std;

using LL = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    for(int i=1; i<=10; i++){
        cout<<rng()%20<<endl;
    }
}

