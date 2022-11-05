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
#define mp make_pair
#define f first
#define s second

pair<ll,ll> get_max(vector<ll>& v){
    pair<ll,ll> maxi=mp(-1,-1);
    forn(0,v.size(),i){
        if(maxi.f<v[i])maxi.f=v[i],maxi.s=i;
    }
    return maxi;
}

void solve(){
    ll a,q;
    cin>>a>>q;
    ll n=log2(a);
    vector<vector<ll>>  v(n+1);
    ll val;
    pair<ll,ll> maxi=mp(-1,-1);
    forn(0,a,i){
        cin>>val;
        v[0].pb(val);
        if(maxi.f<val) maxi.f=val,maxi.s=i;
    }
    ll size;
    vector<pair<ll,ll>> res(n+1,mp(-1,-1));
    res[0]=maxi;
    forn(1,n+1,i){
        size=1<<(n-i);
        vector<ll> temp(size);
        // temp.clear();
        forn(0,size,j){
            if(i%3==1){
                temp[j]=(v[i-1][2*j] ^ v[i-1][2*j+1]);
            }
            else if(i%3==2){
                temp[j]=(v[i-1][2*j] | v[i-1][2*j+1]);
            }
            else{
                temp[j]=(v[i-1][2*j] & v[i-1][2*j+1]);
            }
            if(res[i].f<temp[j]){
                res[i].f=temp[j];
                res[i].s=j;
            }
            // maxi=max(res[i],maxi);
        }
        v[i]=temp;
    }
    // forn(0,n+1,i){
    //     forn(0,v[i].size(),j){
    //         cout<<v[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    // forn(0,n+1,i) cout<<res[i]<<" ";
    // cout<<endl;


    ll index;
    ll one,two;
    ll out=-1;
    forn(0,q,e){
        cin>>index>>val;
        index--;
        // updating all the vectors
        v[0][index]=val;
        if(res[0].s!=index) {
            if(res[0].f<val) res[0].f=val,res[0].s=index;
        }
        else{
            res[0]=get_max(v[0]);
        }
        out=res[0].f;
        // maxi=res[0];
        forn(1,n+1,i){
            // index is odd pick index -1
            one=v[i-1][index];
            if(index&1) two=v[i-1][index-1];
            else two=v[i-1][index+1];
            // updating the value
            if(i%3==1) val=(one^two);
            else if(i%3==2) val=(one | two);
            else val=(one & two);
            index>>=1;
            v[i][index]=val;
            if(res[i].s!=index) {
                if(res[i].f<val) res[i].f=val,res[i].s=index;
            }
            else{
                res[i]=get_max(v[i]);
            }
            // res[i]=max(res[i],val);
            // maxi=max(maxi,res[i]);
            out=max(out,res[i].f);
        }
        cout<<out<<endl;
    }
}

int main(){

    //fastio();
    fileio();
    solve();
    // ll t;
    // t=1;
    // // cin>>t;
    // while(t--){
    //     solve();
    //     cout<<'\n';
    // }
    return 0;
}