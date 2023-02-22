/*
*  Computes the unique solution x to a system of linear congruences (CRT).
*  The system of congruences is of the form x ≡ a[1] (mod m[1]), ..., x ≡ a[n] (mod m[n]),
*  where the moduli m[1], m[2], ..., m[n] are coprime.
*  The function returns x as a single integer modulo M = m[1] * .. * m[n], -1 if not found.
*  Complexity: O(n log(M)), where n is the number of residues and moduli in the system.
*/

#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using PLL = pair<LL, LL>;

tuple <LL,LL,LL> EGCD(LL a, LL b){
    if(b == 0) return {1, 0, a};
    else{
        auto [x,y,g] = EGCD(b, a%b);
        return {y, x - a/b*y,g};
    }
}

PLL CRT(vector <PLL> &v){
    LL V = 0, M = 1;
    for(auto &[v, m]:v){ //value % mod
        auto [x, y, g] = EGCD(M, m);
        if((v - V) % g != 0)
            return {-1, 0};
        V += x * (v - V) / g % (m / g) * M, M *= m / g;
        V = (V % M + M) % M;
    }
    return make_pair(V, M);
}

