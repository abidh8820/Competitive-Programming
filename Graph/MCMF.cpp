/**
Min Cost Max Flow Using Successive Shortest Path
Complexity: SPFA: O(ans*VE) ,
    Dijkstra: O(ans*ElogV) + Cost of Normalization
    Normalization:  Sets potentials (pi) for Dijkstra()
        If all edges >= 0: you may comment out normalize()
        If graph is DAG, use DP in O(m)
        Otherwise, SPFA() is used in O(mn)

Author: anachor
**/


#include<bits/stdc++.h>
using namespace std;
 
namespace MCMF {
    typedef long long F; typedef long long C;
    const F infF = 1e18; const C infC = 1e18;
 
    const int N = 5005;
    typedef pair<C, F> PCF;
 
    struct Edge {int frm, to; C cost; F cap, flow;};
 
    int n, s, t;
    vector<Edge> edges;
    vector<int> adj[N];
    C pi[N], dis[N];
    F fl[N];
    int prv[N], vis[N];
 
    void init(int nodes, int source, int sink) {
        n = nodes, s = source, t = sink;
        for (int i=0; i<n; i++) pi[i] = 0, adj[i].clear();
        edges.clear();
    }
 
    void addEdge(int u, int v, F cap,C cost) {
        edges.push_back({u, v, cost, cap, 0});
        edges.push_back({v, u, -cost, 0, 0});
        adj[u].push_back(edges.size()-2);
        adj[v].push_back(edges.size()-1);
    }
 
    bool SPFA() {
        for (int i=0; i<n; i++) {
            dis[i] = infC; fl[i] = 0;
            vis[i] = 0; prv[i] = -1;
        }
        queue<int> q;
        q.push(s);
        dis[s] = 0; fl[s] = infF; vis[s] = 1;
 
        while (!q.empty()) {
            int u = q.front(); q.pop();
            vis[u] = 0;
            for (int eid : adj[u]) {
                Edge &e = edges[eid];
                if (e.cap == e.flow) continue;
 
                if (dis[u] + e.cost < dis[e.to]) {
                    dis[e.to] = dis[u] + e.cost;
                    fl[e.to] = min(fl[u], e.cap - e.flow);
                    prv[e.to] = eid^1;
                    if (!vis[e.to])     q.push(e.to);
                }
            }
        }
        return fl[t] > 0;
    }
 
    PCF solveSPFA() {
        C cost = 0; F flow = 0;
        while (SPFA()) {
            C pathcost = dis[t];
            cost += pathcost*fl[t]; flow += fl[t];
            for (int u=t, e=prv[u]; e!=-1; u=edges[e].to, e=prv[u]) {
                edges[e].flow -= fl[t];
                edges[e^1].flow += fl[t];
            }
        }
        return {cost, flow};
    }
}
 
const int N = 5005;
int a[N], b[N];
 
int main(){
    int n, p,s;
    cin >> n >> p >> s;
 
 
    for(int i=1; i<=n; i++) cin >> a[i];
    for(int i=1; i<=n; i++) cin >> b[i];
 
    int sports = n+1, progm = n+2, source = n+3, sink = n+4;
 
    MCMF::init(n+10,source, sink);
 
    for(int i=1; i<=n; i++){
        MCMF::addEdge(source,i,1,0);
        MCMF::addEdge(i,progm,1,-a[i]);
        MCMF::addEdge(i,sports,1,-b[i]);
    }
 
    MCMF::addEdge(sports,sink,s,0);
    MCMF::addEdge(progm,sink,p,0);
 
    auto[cost,flow ] = MCMF::solveSPFA();
    cout<< - cost<<endl;
   
    vector<int> sports_, progm_;
 
    for(auto[u,v,cap,cost,flow] : MCMF::edges) {
        if( u>=1 && u<=n  && (v==sports || v==progm) && flow==1) {
            if(v==sports)  sports_.push_back(u);
            else           progm_.push_back(u);
        }
    }
 
    for(int x : progm_) cout << x << ' ';
    cout<<endl;
    for(int x : sports_) cout << x << ' ';
    cout<<endl;
}
