#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL)
#define fileio() freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#define ll long long int
#define forn(l,n,i) for(ll i=l;i<n;i++)

// Order statictic:to get the ith element from sorted position of an  unsorted array in O(n)
// Median of median algorithm

// int PARTITION(vector<int> &a,int l,int r){
//     int i=l-1;
//     int x=a[r];
//     forn(l,r,j){
//         if (a[j]<=x){
//             i++;
//             swap(a[j],a[i]);
//         }
//     }
//     swap(a[i+1],a[r]);
//     return i+1;
// }
int PARTITION(int *a,int l,int r){
    int i=l-1;
    int x=a[r];
    forn(l,r,j){
        if (a[j]<=x){
            i++;
            swap(a[j],a[i]);
        }
    }
    swap(a[i+1],a[r]);
    return i+1;
}
int RANDOMIZED_PARTITION(vector<int> &a,int l,int r){
    int i=(rand()%(r-l+1))+l;
    swap(a[i],a[r]);
    return PARTITION(a,l,r);
}
int ORDER_STATISTIC1(vector<int> &a,int l, int r,int i){
    //best case o(n) and worst case is O(n^2)
    if (l==r){
        return a[l];
    }
    int q=RANDOMIZED_PARTITION(a,l,r);
    int k=q-l+1;
    if (i==k){
        return a[q];
    }
    else if(i<k){
        return ORDER_STATISTIC1(a,l,q-1,i);
    }
    else{
        return ORDER_STATISTIC1(a,q+1,r,i-k);
    }
}
int* FIND_MEDIAN(int *l,int n){
    sort(l,l+n);
    // cout<<*l<<" "<<*(l+n-1)<<" "<<*(l+n/2)<<"\n";
    return l+(n-1)/2;
}
int SELECT( int * a,int l,int r,int i){
    int n=r-l+1;
    if (l==r){
        return a[l];
    }
    else{
        vector<int*> v;
        forn(0,n/5,j){
            v.push_back(FIND_MEDIAN(a+l+j*5,5));
        }
        if (n%5!=0){
            v.push_back(FIND_MEDIAN(a+l+n-n%5,n%5));
        }
        int *c=FIND_MEDIAN(v[0],v.size());
        swap(*c,a[r]);
        int q=PARTITION(a,l,r);
        int k=q-l+1;
        // forn(l,r+1,z){
        //     cout<<a[z]<<" ";
        // }
        // cout<<"\n";
        // cout<<l<<" "<<r<<" "<<*c<<" "<<q<<" "<<k<<" "<<"\n";
        if (i==k){
            return a[q];
        }
        else if(i<k){
            return SELECT(a,l,q-1,i);
        }
        else{
            return SELECT(a,q+1,r,i-k);
        }
    }
}
int main(){
    // fastio();
    // fileio();
    int a[]={5,5,8,8,5,5};
    int n=6;
    forn(1,n+1,i){
        cout<<SELECT(a,0,n-1,i)<<" ";
    }
    return 0;
}
