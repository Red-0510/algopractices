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

void solve(){
    int n;
    cin>>n;
    vector<int> prices(n);
    forn(0,n,i)cin>>prices[i];
    vector<int> res(n+1,0);
    vector<int> dp(n+1,-1);
    dp[0]=0;
    int q;
    forn(1,n+1,i){
        q=INT_MIN;
        forn(1,i+1,j){
            if(q<prices[j-1]+dp[i-j]){
                q=prices[j-1]+dp[i-j];
                res[i]=j;
            }
        }
        dp[i]=q;
    }
    cout<<dp[n]<<endl;
    forn(0,res.size(),i){
        cout<<res[i]<<" ";
    }
    cout<<endl;
    while(n>0){
        cout<<res[n]<<" ";
        n=n-res[n];
    }
    cout<<endl;
}

int main(){

    //fastio();
    fileio();
    solve();
    // ll t;
    // cin>>t;
    // while(t--){
    //     solve();
    //     cout<<'\n';
    // }
    // return 0;
}