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

// update: O(log(NM))
// query:  O(log(NM))
// build:  O(NM(log(NM))
struct BIT2DTree{
    int n,m;
    vector<vector<ll>> container;

    void init(int n,int m){
        this->n=n+1;
        this->m=m+1;
        container.resize(this->n,vector<ll>(this->m,0));
    }

    // returns total sum of elements in rectangle (0,0) to (x,y)
    ll query(int x,int y){
        ll res=0;
        int column;
        while(x>0){
            column=y;
            while(column>0){
                res+=container[x][column];
                column-=column&(-column);
            }
            x-=x&(-x);
        }
        return res;
    }

    // update the value at mat[x][y]=val;
    void update(int x,int y,ll val){
        x++,y++;
        int column;
        while(x<n){
            column=y;
            while(column<m){
                container[x][column]+=val;
                column+=(column&(-column));
            }
            x+=(x&(-x));
        }
    }

    // calculates the sum of rectangle (x1,y1) and (x2,y2)
    ll query(int x1,int y1,int x2,int y2){
        x1++,x2++,y1++,y2++;
        return query(x2,y2)-query(x1-1,y2)- query(x2,y1-1) + query(x1-1,y1-1);
    }

    void print(){
        forn(1,n,i){
            for(int e:container[i]) cout<<e<<" ";
            cout<<endl;
        }
        cout<<"--------"<<endl;
    }
};

void solve(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> mat(n,vector<int>(m,0));
    forn(0,n,i){
        forn(0,n,j) cin>>mat[i][j];
    }

    BIT2DTree tree;
    tree.init(n,m);
    forn(0,n,i){
        forn(0,n,j){
            tree.update(i,j,mat[i][j]);
            // tree.print();
        }
    }
    // cout<<tree.query(3,3)<<endl<<tree.query(1,1,2,2)<<endl;
}

int main(){

    //fastio();
    fileio();
    ll t;
    // cin>>t;
    t=1;
    while(t--){
        solve();
        cout<<'\n';
    }
    return 0;
}