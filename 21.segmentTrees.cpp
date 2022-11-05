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

struct SegmentTree{
    int n;
    vector<int> container;

    void init(int _n){
        this->n=_n;
        container.resize(4*n,0);
    }

    int function(int left,int right){
        return __gcd(left,right);
    }

    void build(int s,int e,int node,vector<int> v){
        if(s==e){
            container[node]=v[s];
            return;
        }
        int mid=(s+e)/2;
        build(s,mid,2*node+1,v);
        build(mid+1,e,2*node+2,v);
        container[node]=function(container[2*node+1],container[2*node+2]);
    }

    int query(int s,int e,int l,int r,int node){
        // non-overlapping case:
        if(s>r || e<l)return 0;
        // complete overlapping case
        else if(s>=l && e<=r) return container[node];
        int mid=(s+e)/2;
        return function(query(s,mid,l,r,2*node+1),query(mid+1,e,l,r,2*node+2));
    }

    void update(int s,int e,int index,int val,int node){
        if(s==e){
            container[node]=val;
            return;
        }
        int mid=(s+e)/2;
        if(mid>=index) update(s,mid,index,val,2*node+1);
        else update(mid+1,e,index,val,2*node+2);
        container[node]=function(container[2*node+1],container[2*node+2]);
    }

    void build(vector<int> v){
        build(0,n-1,0,v);
    }

    int query(int l,int r){
        return query(0,n-1,l,r,0);
    }
    void update(int index,int val){
        update(0,n-1,index,val,0);
    }
};

struct LazySegmenttree{
    int n;
    vector<int> container,lazy;

    void init(int _n){
        n=_n;
        container.resize(4*n);
        lazy.resize(4*n);
    }

    void build(int s,int e,int node,vector<int>& v){
        if(s==e){
            container[node]=v[s];
            return;
        }
        int mid=(s+e)/2;
        build(s,mid,2*node+1,v);
        build(mid+1,e,2*node+2,v);
        container[node]=container[2*node+1]+container[2*node+2];
    }

    int query(int s,int e,int node,int l,int r){
        // no overlapping
        if(s>r || e<l)return 0;

        // update the previous lazy values and propogate
        if(lazy[node]!=0){
            container[node]+=(e-s+1)*lazy[node];
            if(s!=e){
                lazy[2*node+1]=1-lazy[2*node+1];
                lazy[2*node+2]=1-lazy[2*node+2];
            }
            lazy[node]=0;
        }
        // complete overlap
        if(s>=l && e<=r){
            return container[node];
        }
        //partial overlap
        int mid=(s+e)/2;
        return query(s,mid,2*node+1,l,r)+query(mid+1,e,2*node+2,l,r);
    }

    void update(int s,int e,int node,int l,int r,int val){
        // no overlap
        if(s>r || e<l) return;
        // update previous lazy , propogate and add current update
        if(lazy[node]!=0){
            container[node]+=(e-s+1)*lazy[node];
            if(s!=e){
                lazy[2*node+1]=lazy[node];
                lazy[2*node+2]=lazy[node];
            }
        }
        // complete overlap
        if(s>=l && e<=r){
            container[node]+=(e-s+1)*val;
            if(s!=e){
                lazy[2*node+1]=val;
                lazy[2*node+2]=val;
            }
            return;
        }
        int mid=(s+e)/2;
        update(s,mid,2*node+1,l,r,val);
        update(mid+1,e,2*node+2,l,r,val);
        container[node]=container[2*node+1]+container[2*node+2];
    }

    void update(int l,int r,int val){
        update(0,n-1,0,l,r,val);
    }
    int query(int l,int r){
        return query(0,n-1,0,l,r);
    }
    void build(vector<int>& v){
        build(0,n-1,0,v);
    }
};

int main(){
    //fastio();
    fileio();
    vector<int> v={1,2,3,4,5,6,7,8,9};
    LazySegmenttree tree;
    tree.init(v.size());
    tree.build(v);
    cout<<tree.query(0,3)<<endl;
    tree.update(0,3,5);
    cout<<tree.query(0,3)<<endl;
    cout<<tree.query(0,0)<<endl;
    cout<<tree.query(1,1)<<endl;
    tree.update(1,5,3); 
    cout<<tree.query(3,3)<<endl;
    cout<<tree.query(0,3)<<endl;
    return 0;
}