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


// Prims Algorithm
void solve(){
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,int>>> g(n+1,vector<pair<int,int>>());
    forn(0,m,i){
        int a,b,w;
        cin>>a>>b>>w;
        g[a].pb({b,w});
        g[b].pb({a,w});
    }
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    ll res=0;
    pq.push({0,1});
    vector<bool> visited(n+1,false);
    while(!pq.empty()){
        auto cur=pq.top();
        pq.pop();
        if(!visited[cur.S]){
            for(auto x:g[cur.S]){
                if(!visited[x.F]){
                    pq.push({x.S,x.F});
                }
            }
            res+=cur.F;
            visited[cur.S]=true;
        }
    }
    cout<<res;
}

class DSU{
    vector<int> parent,rank;
    int n;
    public:
    DSU(int n){
        this->n=n;
        parent.resize(this->n+1,-1);
        rank.resize(this->n+1,1);
    }
    int find(int x){
        if(parent[x]==-1) return x;
        return parent[x]=find(parent[x]);
    }

    bool unite(int a,int b){
        a=find(a);
        b=find(b);
        if(a==b) return true;
        else{
            if(rank[a]>=rank[b]) {
                parent[b]=a;
                rank[a]+=rank[b];
            }
            else{
                parent[a]=b;
                rank[b]+=rank[a];
            }
            return false;
        }
    }
};

void solve(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> edges(m,vector<int>(3));
    int a,b,w;
    forn(0,m,i){
        cin>>edges[i][1]>>edges[i][2]>>edges[i][0];
    }
    sort(edges.begin(),edges.end());
    DSU d(n);
    ll res=0;
    for(auto x:edges){
        if(!d.unite(x[1],x[2])) res+=x[0];
    }
    cout<<res;
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