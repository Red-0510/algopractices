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
    int n,m;
    cin>>n>>m;
    vector<vector<int>> dist(n,vector<int>(n,INT_MAX));
    int a,b,w;
    forn(0,m,i){
        cin>>a>>b>>w;
        dist[a-1][b-1]=w;
    }
    forn(0,n,i)dist[i][i]=0;
    int s,e;
    cin>>s>>e;
    forn(0,n,l){
        forn(0,n,i){
            forn(0,n,j){
                if(dist[i][j]>dist[i][l]+dist[l][j] && dist[i][l]!=INT_MAX && dist[l][j]!=INT_MAX){
                    dist[i][j]=dist[i][l]+dist[l][j];
                }
            }
        }
    }
    if(dist[s-1][e-1]==INT_MAX) cout<<"NO";
    else cout<<dist[s-1][e-1];
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