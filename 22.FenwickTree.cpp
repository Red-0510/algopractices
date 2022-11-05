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

struct FenwickTree{
    int n;
    vector<int> container;
    void init(int n){
        this->n=n+1; // for 1 based indexing
        container.resize(this->n,0);
    }

    void update(int index,int val){
        index++;// 2 based indexing
        while(index<n){
            container[index]+=val;
            index+=(index&(-index));
        }
    }

    int query(int index){
        index ++;
        int ans=0;
        while(index){
            ans+=container[index];
            index-=(index&(-index));
        }
        return ans;
    }

    int query(int l,int r){
        return query(r) -query(l-1);
    }
};

int main(){

    //fastio();
    fileio();
    vector<int> v={1,2,3,4,5,6,7};
    FenwickTree tree;
    tree.init(v.size());
    forn(0,v.size(),i){
        tree.update(i,v[i]);
    }
    cout<<tree.query(3,4);
    tree.update(3,-2);
    cout<<tree.query(3,4);
    return 0;
}