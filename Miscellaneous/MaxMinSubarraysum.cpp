#include <bits/stdc++.h>
using namespace std;

struct Seg {
    int minPref, maxPref, minSuff, maxSuff, maxseg, minseg, tot;
    Seg(int x = 0) {
        tot = x;
        minPref = minSuff = minseg = min(0, x);
        maxPref = maxSuff = maxseg = max(0, x);
    }
};

Seg merge(Seg& left, Seg& right) {
    Seg ret;
    ret.tot = left.tot + right.tot;
    ret.maxPref = max(left.maxPref, left.tot + right.maxPref);
    ret.maxSuff = max(right.maxSuff, right.tot + left.maxSuff);
    ret.maxseg = max({left.maxseg, right.maxseg, left.maxSuff + right.maxPref});
 
    ret.minPref = min(left.minPref, left.tot + right.minPref);
    ret.minSuff = min(right.minSuff, right.tot + left.minSuff);
    ret.minseg = min({left.minseg, right.minseg, left.minSuff + right.minPref});
    return ret;
}


