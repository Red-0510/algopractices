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

int power(int a,int b){
    int res=1;
    while(b){
        if(b&1) res*=a;
        a*=a;
        b>>=1;
    }
    return res;
}

ll powermodM(ll a,ll b,ll m){
    ll res=1;
    while(b){
        if(b&1) res*=a, res%=m;
        a*=a;
        a%=m;
        b>>=1;
    }
    return res;
}

int mult(int a,int b){
    int res=0;
    while(b){
        if(b&1) res+=a;
        a<<=1;
        b>>=1;
    }
    return res;
}

ll multmodM(ll a,ll b,ll m){
    ll res=0;
    while(b){
        if(b&1) res+=a,res%=m;
        a+=a;
        a%=m;
        b>>=1;
    }
    return res;
}

// matrix exponentiation
const int SIZE=2;
const ll MOD=1e9+7;
struct Mat{
    ll m[SIZE][SIZE];
    Mat(){
        memset(m,0,sizeof(m));
    }

    void identity(){
        for(int i=0;i<SIZE;i++)m[i][i]=1;
    }

    Mat operator*(Mat a){
        Mat res;
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){
                for(int k=0;k<SIZE;k++){
                    res.m[i][j]+=(m[i][k]*a.m[k][j])%MOD;
                }
            }
        }
        return res;
    }
    void display(){
        forn(0,SIZE,i){
            forn(0,SIZE,j) cout<<m[i][j]<<" ";
            cout<<endl;
        }
        cout<<"-------"<<endl;
    }
};

ll fib(int n){
    if(n<3) return 1;
    Mat T,res;
    res.identity();
    T.m[0][0]=T.m[0][1]=T.m[1][0]=1;
    n-=2;
    while(n){
        if(n&1) res=res*T;
        T=T*T;
        n>>=1;
    }
    return (res.m[0][0]+res.m[0][1])%MOD;
}

void solve(){
    int n;
    cin>>n;
    cout<<fib(n);
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