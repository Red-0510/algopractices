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
    vector<vector<pair<ll,ll>>> g(n+1,vector<pair<ll,ll>>());
    forn(0,m,i){
        ll a,b,w;
        cin>>a>>b>>w;
        g[a].pb({b,w});
    }
    ll s,e;
    cin>>s>>e;
    ll inf=1e18;
    vector<ll> dist(n+1,inf);
    dist[s]=0;
    set<pair<ll,ll>> paths;
    paths.insert({0,s});
    while(!paths.empty()){
        auto it=paths.begin();
        ll cur=it->second;
        ll till=it->first;
        paths.erase(it);
        for(auto [nbr,w] : g[cur]){
            if(till+w<dist[nbr]){
                auto f=paths.find({dist[nbr],nbr});
                if(f!=paths.end()) paths.erase(f);
                dist[nbr]=till+w;
                paths.insert({dist[nbr],nbr});
            }
        }
    }
    if(dist[e]==inf) cout<<"NO";
    else cout<<dist[e];
}

int main(){

    //fastio();
    fileio();
    ll t;
    cin>>t;
    while(t--){
        solve();
        cout<<'\n';
    }
    return 0;
}

// 3
// 3 2
// 1 2 5
// 2 3 7
// 1 3
// 3 3
// 1 2 4
// 1 3 7
// 2 3 1
// 1 3
// 3 1
// 1 2 4
// 1 3