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

const int N=1e5+1;
vector<int> g[N];
// // O(N)  N-number of nodes
// int dep[N],par[N];

// void dfs(int cur,int p){
//     dep[cur]=dep[p]+1;
//     par[cur]=p;
//     for(int x:g[cur]){
//         if(x!=p){
//             dfs(x,cur);
//         }
//     }
// }

// // return lowest common ancestors
// int LCA(int u,int v){
//     if(u==v) return u;
//     if(dep[u]<dep[v]) swap(u,v);
//     // depth of u is more than depth of v
//     int diff=dep[u]-dep[v];
//     // getting both u and v at the same depth level
//     while(diff--) u=par[u];
//     while(u!=v){
//         u=par[u];
//         v=par[v];
//     }
//     return u;
// }   

// using sparse table and binary lifting 
// O(logn for each query and NlogN for creating the sparse table)
// const int M=20;// logN
// int dep[N],par[N][M];

// void dfs(int cur,int p){
//     dep[cur]=dep[p]+1;
//     par[cur][0]=p;
//     forn(1,M,i){
//         par[cur][i]=par[par[cur][i-1]][i-1];
//     }
//     for(int x:g[cur]){
//         if(x!=p){
//             dfs(x,cur);
//         }
//     }
// }

// int LCA(int u,int v){
//     if(u==v) return u;
//     if(dep[u]<dep[v]) swap(u,v);
//     int diff=dep[u]-dep[v];
//     for(int i=M-1;i>=0;i--){
//         if(diff&(1<<i)) u=par[u][i];
//     }
//     for(int i=M-1;i>=0;i--){
//         if(par[u][i]!=par[v][i]){
//             u=par[u][i];
//             v=par[v][i];
//         }
//     }
//     if(u==v) return u;
//     else return par[u][0];
// }


// LCA queries in O(1) using eular tour sparse Tables
int dep[N]={0};
int start[N]={0};
struct sparseTable{
    int n;
    int m;
    vector<vector<int>> container;

    void init(int _n){
        n=_n;
        m=log2(n)+1;
        container.resize(m+1,vector<int>(n,INT_MAX));
    }
    void build(vector<int>  &v){
        forn(0,n,i) container[0][i]=v[i];
        forn(1,m+1,i){
            for(int j=0;j+(1<<i)<=n;j++){
                int a=container[i-1][j];
                int b=container[i-1][j+(1<<(i-1))];
                container[i][j]=(dep[b]<dep[a])?b:a;
            }
        }
    }

    int query(int u,int v){
        int len=log2(v-u+1);
        int a=container[len][u];
        int b=container[len][v-(1<<len)+1];
        return (dep[b]<dep[a])?b:a;
    }
};

void dfs(int cur,int p,vector<int>& tour){
    start[cur]=tour.size();
    tour.pb(cur);
    dep[cur]=dep[p]+1;
    for(int x:g[cur]){
        if(x!=p){
            dfs(x,cur,tour);
            tour.pb(cur);
        }
    }
}


int main(){

    //fastio();
    fileio();
    int n;
    cin>>n;
    forn(0,n-1,i){
        int x,y;
        cin>>x>>y;
        g[x].pb(y);
        g[y].pb(x);
    }
    vector<int> tour;
    dfs(1,0,tour);
    sparseTable t;
    t.init(tour.size());
    t.build(tour);
    int q;
    cin>>q;
    forn(0,q,i) {
        int a,b;
        cin>>a>>b;
        cout<<t.query(min(start[a],start[b]),max(start[a],start[b]))<<" ";
    }
    // cout<<LCA(9,12)<<" "<<LCA(10,8)<<" "<<LCA(9,11)<<endl;
    return 0;
}