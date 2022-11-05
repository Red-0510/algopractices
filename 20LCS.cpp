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

string getstring(string s1,string s2,vector<vector<pair<int,int>>>& res,int i,int j){
    string str="";
    while(i>0 && j>0){
        if(res[i][j].s==1) str=s1[i-1]+str,i--,j--;
        else if(res[i][j].s==0) i--;
        else j--;
    }
    return str;
}

// DP based memoisation
string lcs(string s1,string s2,vector<vector<pair<int,int>>>& res){
    forn(0,s1.length(),i){
        forn(0,s2.length(),j){
            if(s1[i]==s2[j]) {
                res[i+1][j+1]=mp(res[i][j].f+1,1);
            }
            else if(res[i][j+1].f>=res[i+1][j].f){
                res[i+1][j+1]=mp(res[i][j+1].f,0);
            }
            else{
                res[i+1][j+1]=mp(res[i+1][j].f,2);
            }
        }
    }
    return getstring(s1,s2,res,s1.length(),s2.length());
}

// recursive algorithm
string lcs2(string s1,string s2,int i,int j){
    string res="";
    if(s1[i]=='\0' || s2[j]=='\0') return res;
    else if(s1[i]==s2[j]){
        return s1[i]+lcs2(s1,s2,i+1,j+1);
    }
    else {
        string sub1=lcs2(s1,s2,i+1,j);
        string sub2=lcs2(s1,s2,i,j+1);
        if(sub1.length()>=sub2.length()) return sub1;
        else return sub2;
    }
}

void solve(){
    string s1,s2;
    cin>>s1>>s2;
    vector<vector<pair<int,int>>> v(s1.length()+1,vector<pair<int,int>>(s2.length()+1));
    forn(0,s1.length()+1,i){
        v[i][0]=mp(0,0);
    }
    forn(0,s2.length()+1,i){
        v[0][i]=mp(0,0);
    }
    // string res="";
    string res=lcs(s1,s2,v);
    cout<<res.length()<<" "<<res;
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