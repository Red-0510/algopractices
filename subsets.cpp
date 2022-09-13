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


void subsets(vector<int> &v,vector<int>& subset,int i){
    if(i==v.size()){
        if(subset.size()==0) cout<<"NUll";
        for(int x:subset) cout<<x<<" ";
        // subset.clear();
        cout<<endl;
    }
    else{
        subset.pb(v[i]);
        subsets(v,subset,i+1);
        subset.ppb();
        subsets(v,subset,i+1);
    }
}


void permute(vector<int> &v,vector<bool> &selected,vector<int>& permutations){
    if(permutations.size()==v.size()){
        for(int x:permutations) cout<<x<<" ";
        cout<<endl;
    }
    else{
        forn(0,v.size(),i){
            if(selected[i]) continue;
            selected[i]=true;
            permutations.pb(v[i]);
            permute(v,selected,permutations);
            selected[i]=false;
            permutations.ppb();
        }
    }
}
int main(){

    //fastio();
    fileio();
    int n;
    cin>>n;
    vector<int> v(n,0);
    forn(0,n,i){
        cin>>v[i];
    }
    // vector<int> subset;
    // subsets(v,subset,0);

    vector<int> permutations;
    vector<bool> selected(n,false);
    permute(v,selected,permutations);
    return 0;
}