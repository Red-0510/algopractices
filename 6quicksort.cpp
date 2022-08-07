
// QUICKSORT ALGORITHM
#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL)
#define fileio() freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#define ll long long int
#define forn(l,n,i) for(ll i=l;i<n;i++)

// procedures:
// 1)RANDOMIZED_PARTITION()

int PARTITION(vector<int> &a,int l,int r){
    int i=l-1;
    int x=a[r];
    forn(l,r,j){
        if (a[j]<=x){
            i++;
            swap(a[j],a[i]);
        }
    }
    swap(a[i+1],a[r]);
    return (i+1);
}

int RANDOMIZED_PARTITION(vector<int> &a,int l,int r){
    int i=(rand()%(r-l+1))+l;
    swap(a[i],a[r]);
    return PARTITION(a,l,r);
}
void printarr(vector<int> &a){
    forn(0,a.size(),i){
        cout<<a[i]<<" ";
    }
    cout<<"\n";
}

void RANDOMIZED_QUICKSORT(vector<int> &a,int l,int r){
    if (r>l){
        int q=RANDOMIZED_PARTITION(a,l,r);
        RANDOMIZED_QUICKSORT(a,l,q-1);
        RANDOMIZED_QUICKSORT(a,q+1,r);
    }
}

int main(){
    srand(time(NULL));
    vector<int> a={5,6,3,7,2,8,5};
    int s=a.size();
    printarr(a);
    RANDOMIZED_QUICKSORT(a,0,s-1);
    printarr(a);
    return 0;
}