#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;

#define fastio() iosbase_::sync_with_stdio(false);cin.tie(NULL);
#define fileio() freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
#define ll long long int
#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define forn(l,n,i) for(ll i=l;i<n;i++) 

// void printTree(vector<vector<int>>& res,int i,int j){
//     forn(0)
// }

void solve(){
    int n;
    cin>>n;
    vector<int> p(n);
    vector<int> d(n+1);
    forn(0,n,i)cin>>p[i];
    forn(0,n+1,i) cin>>d[i];
    
    vector<vector<int>> v(n+1,vector<int>(n+1));
    vector<vector<int>> w(n+1,vector<int>(n+1));
    vector<vector<int>> res(n,vector<int>(n));
    forn(0,n+1,i){
        v[i][i]=d[i];
        w[i][i]=d[i];
    }
    forn(1,n+1,len){
        forn(0,n-len+1,i){
            int j=i+len;
            v[i][j]=INT_MAX;
            w[i][j]=w[i][j-1]+p[j-1]+d[j];
            int t;
            forn(i,j,r){
                t=v[i][r]+v[r+1][j]+w[i][j];
                if(t<v[i][j]){
                    v[i][j]=t;
                    res[i][j-1]=r;
                }
            }
        }
    }
    cout<<v[0][n]<<endl;
    // printTree(res,0,n-1);
    forn(0,n+1,i){
        forn(0,n+1,j) cout<<v[i][j]<<" ";
        cout<<endl;
    }
    cout<<"-----------\n";
    forn(0,n+1,i){
        forn(0,n+1,j){
            cout<<w[i][j]<<" ";
        }
        cout<<endl;
    }
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