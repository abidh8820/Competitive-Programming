#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;
using LL = long long;

struct SuffixAutomaton {
    struct Node {
        int len = 0, link = -1, first_pos = 0;
        bool is_clone = false;
        map<char, int> next;
    };

    int sz = 1, last = 0;
    vector<Node> states;
    vector<int> terminal, dp;
    vector<vector<int>> adj;

    SuffixAutomaton(int n) : states(2 * n), terminal(2 * n, 0), dp(2 * n, -1), adj(2 * n) {}

    void extend(char c) {
        int p = last, cur = sz++, clone;
        if (states[p].next.count(c)) {

            int q = states[p].next[c];
            if (states[q].len == states[p].len + 1) { last = q; return; }
            states[clone = sz++] = states[q];
            states[clone].len = states[p].len + 1; states[clone].is_clone = true;
            states[q].link = clone;

            while (p != -1 && states[p].next[c] == q) states[p].next[c] = clone, p = states[p].link;
            last = clone;
            return;
        }

        states[cur].len = states[last].len + 1;
        states[cur].first_pos = states[cur].len;
        while (p != -1 && !states[p].next.count(c)) states[p].next[c] = cur, p = states[p].link;

        if (p == -1) states[cur].link = 0;
        else {
            int q = states[p].next[c];
            if (states[p].len + 1 == states[q].len) states[cur].link = q;
            else {
                states[clone = sz++] = states[q];
                states[clone].len = states[p].len + 1; states[clone].is_clone = true;
                while (p != -1 && states[p].next[c] == q) states[p].next[c] = clone, p = states[p].link;
                states[q].link = states[cur].link = clone;
            }
        }
        last = cur;
    }

    void build_tree() { for (int i = 1; i < sz; ++i) adj[states[i].link].push_back(i); }

    void build(const string &s) {
        for (char x : s) extend(x), terminal[last] = 1;
        build_tree();
    }

    long long count_occurrences(int i) { //number of times i-th node occurs in the string
        if (dp[i] != -1) return dp[i];
        long long result = terminal[i];
        for (int child : adj[i]) result += count_occurrences(child);
        return dp[i] = result;
    }

    long long count_unique_substrings() {
        long long count = 0;
        for (int i = 1; i < sz; ++i) count += states[i].len - states[states[i].link].len;
        return count;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s; cin >> s;
    SuffixAutomaton sa(s.size());
    sa.build(s);

    int q;
    cin >> q;

    while(q--){
        int cur = 0;
        string s;
        cin >> s;

        bool ok = true;
        for(char c : s){
            if(!sa.states[cur].next.count(c)){ok = false; break;} 
            else cur = sa.states[cur].next[c];
        }

        if(!ok) cout << -1 << "\n";
        else cout << sa.states[cur].first_pos - (int)s.size() + 1 << '\n';

    }
}
//finds first occurance
