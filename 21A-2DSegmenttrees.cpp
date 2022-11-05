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

struct SegmentTree2D{
    int n,m;
    vector<vector<ll>> container;

    void init(int n,int m){
        this->n=n;
        this->m=m;
        container.resize(4*this->n,vector<ll>(4*this->m));
    }
    // build segment tree for a individual row or adds to segment tree to create a new segment tree
    void buildcolumn(int startx,int endx,int nodex,int starty,int endy,int nodey,vector<vector<int>>&mat){
        if(starty==endy){
            if(startx==endx) container[nodex][nodey]=mat[startx][starty];
            else{
                container[nodex][nodey]=container[2*nodex+1][nodey]+container[2*nodex+2][nodey];
            }
        }
        else{
            int mid=(starty+endy)/2;
            buildcolumn(startx,endx,nodex,starty,mid,2*nodey+1,mat);
            buildcolumn(startx,endx,nodex,mid+1,endy,2*nodey+2,mat);
            container[nodex][nodey]=container[nodex][2*nodey+1]+container[nodex][2*nodey+2];
        }
    }


    // builds segment tree by combaining segment trees of different rows
    void buildrow(int startx,int endx,int nodex,vector<vector<int>>& mat){
        // builds segment tree for a single row
        if(startx==endx){
            buildcolumn(startx,endx,nodex,0,m-1,0,mat);
        }
        else{
            int mid=(startx+endx)/2;
            buildrow(startx,mid,2*nodex+1,mat);
            buildrow(mid+1,endx,2*nodex+2,mat);
            buildcolumn(startx,endx,nodex,0,m-1,0,mat);
        }
    }

    // narrows query to return from single segment tree or (sum through column)
    ll querycolumn(int nodex,int starty,int endy,int nodey,int y1,int y2){
        if(endy<y1 || starty>y2) return 0;
        else if(starty>=y1 && endy<=y2){
            return container[nodex][nodey];
        }
        else{
            int mid=(starty+endy)/2;
            ll left=querycolumn(nodex,starty,mid,2*nodey+1,y1,y2);
            ll right=querycolumn(nodex,mid+1,endy,2*nodey+2,y1,y2);
            return left+right;
        }
    }

    // narrows query to group/individual segment trees or (sum for the row values)
    ll queryrow(int startx,int endx,int nodex,int x1,int x2,int y1,int y2){
        if(endx<x1 || startx>x2) return 0;
        else if(startx>=x1 && endx<=x2){
            return querycolumn(nodex,0,m-1,0,y1,y2);
        }
        else{
            int mid=(startx+endx)/2;
            ll left=queryrow(startx,mid,2*nodex+1,x1,x2,y1,y2);
            ll right=queryrow(mid+1,endx,2*nodex+2,x1,x2,y1,y2);
            return left+right;
        }
    }

    // propogates in the single Segment Tree and upadtes all the required position
    void updatecolumn(int nodex,int startx,int endx,int starty,int endy,int nodey,int y,int val){
        if(starty==endy){
            if(startx==endx) container[nodex][nodey]=val;
            else{
                container[nodex][nodey]=container[2*nodex+1][nodey]+container[2*nodex+2][nodey];
            }
        }
        else{
            int mid=(starty+endy)/2;
            if(mid>=y) updatecolumn(nodex,startx,endx,starty,mid,2*nodey+1,y,val);
            else updatecolumn(nodex,startx,endx,mid+1,endy,2*nodey+2,y,val);
            container[nodex][nodey]=container[nodex][2*nodey+1]+container[nodex][2*nodey+2];
        }
    }

    // propogates through the effecting row(segment tree) column updates that cell and retraces back to update all the ancestors Segment trees
    void updaterow(int startx,int endx,int nodex,int x,int y,int val){
        // got the effecting Segment Tree
        if(startx==endx){
            updatecolumn(nodex,startx,endx,0,m-1,0,y,val);
        }
        else {
            int mid=(startx+endx)/2;
            if(mid>=x) updaterow(startx,mid,2*nodex+1,x,y,val);
            else updaterow(mid+1,endx,2*nodex+2,x,y,val);
            updatecolumn(nodex,startx,endx,0,m-1,0,y,val);
        }
    }

    // helper to build a 2D segment tree
    void build(vector<vector<int>>& mat){
        init(mat.size(),mat[0].size());
        buildrow(0,n-1,0,mat);
    }

    // helper for a 2D sum query
    ll query(int x1,int x2,int y1,int y2){
        return queryrow(0,n-1,0,x1,x2,y1,y2);
    }

    // helper for updating a value in the matrix
    // mat[x][y]=val
    void update(int x,int y,int val){
        updaterow(0,n-1,0,x,y,val);
    }

    void print(){
        for(vector<ll> x:container) {
            for(int e:x) cout<<e<<" ";
            cout<<endl;
        }
    }
};

void solve(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> mat(n,vector<int>(m));
    forn(0,n,i) {
        forn(0,m,j) cin>>mat[i][j];
    }
    SegmentTree2D tree;
    tree.build(mat);
    tree.print();
    cout<<tree.query(1,2,1,2)<<endl;
    tree.update(1,2,2);
    tree.print();
    cout<<tree.query(1,2,1,2);
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