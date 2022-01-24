
typedef long long LL;
 
const LL N = 1e6 + 7;
const LL M = 1e9 + 7;
const LL P = 29;
 
LL pp[N];
 
void pre() {
    pp[0] = 1;
    for (int i = 1; i < N; i++) pp[i] = (pp[i - 1] * P) % M;
}
 
// prefix hash of the string
vector<LL> prefixhash(string& s) {
    int n = s.size();  vector<LL> hashlist(n);
    hashlist[0] = 1LL * (s[0] - 'a');
    for (int i = 1; i < n; i++) {
        hashlist[i] = (hashlist[i - 1] * P + s[i] - 'a') % M;
    }
    return hashlist;
}
 
// hash of a substring
LL subhash(int i, int j, const vector<LL>& hashlist) {
    if (i == 0) return hashlist[j];  int len = -i + j + 1;
    return (hashlist[j] - (hashlist[i - 1] * pp[len]) % M + M) % M;
}
