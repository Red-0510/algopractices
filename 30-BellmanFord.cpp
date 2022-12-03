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

void solve(){
    ll n,m;
    cin>>n>>m;
    vector<vector<ll>> v(m,vector<ll>(3));
    forn(0,m,i){
        cin>>v[i][0]>>v[i][1]>>v[i][2];
    }
    ll inf=1e18;
    vector<ll> dist(n+1,inf);
    dist[1]=0;
    forn(0,n-1,_){
        for(auto x:v){
            if(dist[x[0]]!=inf && dist[x[0]]+x[2]<dist[x[1]]){
                dist[x[1]]=dist[x[0]]+x[2];
            }
        }
    }
    forn(1,n+1,i){
        if(dist[i]==inf) cout<<30000<<" ";
        else cout<<dist[i]<<" ";
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
