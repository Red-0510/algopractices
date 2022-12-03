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

class dsu{
    int n;
    vector<int> parent;
    vector<int> rank;
    public:
    dsu(int n){
        this->n=n;
        parent.resize(n+1,-1);
        rank.resize(n+1,1);
    }
    int find(int x){
        if(parent[x]==-1) return x;
        // return find(parent[x]);
        // path compression
        return parent[x]=find(parent[x]);
    }

    // returns true on loop detection
    bool union_set(int a,int b){
        int s1=find(a);
        int s2=find(b);
        if(s1!=s2){
            // union by rank
            if(rank[s1]>=rank[s2]){
                parent[s2]=s1;
                rank[s1]+=rank[s2];
            }
            else{
                parent[s1]=s2;
                rank[s2]+=rank[s1];
            }
            return false;
        } 
        else return true;
    }
    
};

vector<bool> DSU(vector<vector<int>>query){
    int n=1e5+2;
    dsu d(n);
    vector<bool> res;
    for(auto x:query){
        if(x[0]==1){
            d.union_set(x[1],x[2]);
        }
        else{
            if(d.find(x[0])==d.find(x[1])) res.pb(true);
            else res.pb(false);
        }
    }
    return res;
}

void solve(){
    int n;
    cin>>n;
    vector<vector<int>> query(n,vector<int>(3));
    forn(0,n,i){
        cin>>query[i][0]>>query[i][1]>>query[i][2];
    }
    for(int x:DSU(query)) cout<<x<<" ";
}

int main(){

    //fastio();
    fileio();
    solve();
}