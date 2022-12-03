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

struct node{
    int indegree=0;
    list<int> nbrs;
};

vector<node> g;

// using Kahns Algorithm underlying algorihtm BFS
vector<int> solve(int n,int m, vector<vector<int>> arr){
    g=vector<node>(n+1,node());
    for(auto x:arr){
        g[x[0]].nbrs.pb(x[1]);
        g[x[1]].indegree++;
    }
    queue<int> s;
    vector<int> res;
    forn(1,n+1,i){
        if (g[i].indegree==0) s.push(i);
    }
    while(!s.empty()){
        int cur=s.front();
        res.pb(cur);
        s.pop();
        for(int x:g[cur].nbrs){
            g[x].indegree--;
            if(g[x].indegree==0) s.push(x);
        }
    }  
    if(res.size()==n) return res;
    return vector<int>();
}


// DFS based algorithm
// void dfs(int cur,vector<node>& g,vector<bool>&visited,vector<int>& res){
//     visited[cur]=true;
//     for(int x:g[cur].nbrs){
//         if(!visited[x]) {
//             dfs(x,g,visited,res);
//         }
//     }
//     res.pb(cur);
// }

// vector<int> solve(int n,int m,vector<vector<int>> arr){
//     g=vector<node>(n+1,node());
//     for(auto x:arr){
//         g[x[0]].nbrs.pb(x[1]);
//     }
//     vector<bool> visited(n+1,false);
//     vector<int> res;
//     forn(1,n+1,i){
//         if(!visited[i]){
//             dfs(i,g,visited,res);
//         }
//     }
//     if(res.size()==n) {
//         reverse(res.begin(),res.end());
//         return res;
//     }
//     else return vector<int>();
// }

void solve2(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> v(m,vector<int>(2));
    forn(0,m,i){
        cin>>v[i][0]>>v[i][1];
    }
    for(int x:solve(n,m,v)) cout<<x<<" ";
}

int main(){

    //fastio();
    fileio();
    solve2();
}