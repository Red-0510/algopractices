#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;

#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);
#define fileio() freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
#define ll long long int
#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define forn(l,n,i) for(ll i=l;i<n;i++)
#define mp make_pair
#define F first
#define S second 
// Range minimum query using sparse table
// building nlogn
// query(which are independent on overlapping ranges) O(1)
// useful for immutable data i.e. no updation as updation will need to be buid again in nlogn

struct SparseTable{
    int n,m;
    vector<vector<ll>> container;
    void init(int _n){
        n=_n;
        m=log2(n)+1;
        container.resize(m,vector<ll>(n,INT_MAX));
    }

    void build(vector<ll>& v){
        forn(0,n,i)container[0][i]=v[i];
        forn(1,m,i){
            for(int j=0;j+(1<<i)<=n;j++){
                container[i][j]=min(container[i-1][j],container[i-1][j+(1<<(i-1))]);
            }
        }
    }

    ll query(int u,int v){
        int len=log2((v-u+1));
        return min(container[len][u],container[len][v-(1<<len)+1]);
    }

    void print(){
        for(auto x: container){
            for(ll y:x) cout<<y<<" ";
            cout<<endl;
        }
    }
};

void solve(){
    ll n;
    cin>>n;
    vector<ll> v(n);
    forn(0,n,i) cin>>v[i];
    SparseTable t;
    t.init(n);
    t.build(v);
    int q;
    cin>>q;
    // t.print();
    forn(0,q,i){
        int a,b;
        cin>>a>>b;
        cout<<t.query(min(a,b),max(a,b))<<" ";
    }
}

int main(){

    //fastio();
    fileio();
    ll t;
    // cin>>t;
    t=1;
    while(t--){
        solve();
        cout<<'\n';
    }
    return 0;
}