#include<bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r){
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
// Random n numbers between l and r
void num(int l, int r, int n) {
    for (int i = 0; i < n; ++i)
    {
        cout << rnd(l,r) << " ";
    }
}
 
//Random n real numbers between l and r with dig decimal places
void real(int l, int r, int dig, int n) {
    for (int i = 0; i < n; ++i)
    {
        cout << rnd(l,r) <<"."<<rnd(0,pow(10,dig)-1)<< " ";
    }
}
// Random n strings of length l
void str(int l, int n) {
    for (int i = 0; i < n; ++i)
    {
        for(int j = 0; j < l; ++j) {
            int v = rnd(1,150);
            if(v%3==0) cout<<(char)rnd('a','z');
            else if(v%3==1) cout<<(char)rnd('A','Z');
            else cout<<rnd(0,9);
        }
        cout<<" ";
    }
}
// Random n strings of max length l
void strmx(int mxlen, int n) {
    for (int i = 0; i < n; ++i)
    {
        int l = rnd(1,mxlen);
        for(int j = 0; j < l; ++j) {
            int v = rnd(1,150);
            if(3%3==0) cout<<(char)rnd('a','z');
            else if(v%3==1) cout<<(char)rnd('A','Z');
            else cout<<rnd(0,9);
        }
        cout<<" ";
    }
} 
// Random tree of n nodes
void tree(int n) {
    int prufer[n-2];
    for ( int i = 0; i < n; i++ ){
        prufer[i] = rnd(1,n);
    }
    int m = n-2;
    int vertices = m + 2; 
    int vertex_set[vertices]; 
    for (int i = 0; i < vertices; i++) 
        vertex_set[i] = 0; 
    for (int i = 0; i < vertices - 2; i++) 
        vertex_set[prufer[i] - 1] += 1; 
    int j = 0; 
    for (int i = 0; i < vertices - 2; i++) { 
        for (j = 0; j < vertices; j++) { 
            if (vertex_set[j] == 0) { 
                vertex_set[j] = -1; 
                cout << (j + 1) << " "
                     << prufer[i] << '\n'; 
                vertex_set[prufer[i] - 1]--; 
                break; 
            } 
        } 
    } 
    j = 0; 
    for (int i = 0; i < vertices; i++) { 
        if (vertex_set[i] == 0 && j == 0) { 
            cout << (i + 1) << " "; 
            j++; 
        } 
        else if (vertex_set[i] == 0 && j == 1) 
            cout << (i + 1) << "\n"; 
    }
}

signed main()
{
    int t = 1;
    cout << t << endl;

    int n = rng() % 9 + 1;
    int m = rng() % 3 + 1;
    cout << n <<" "<< m <<endl;

    string goods = "xnbareky";
    for(int i=0; i < n; i++){
        for(int j =0 ; j < m; j++){
            cout << goods[rng() % 8];
        }
        cout <<endl;
    }
    
}
