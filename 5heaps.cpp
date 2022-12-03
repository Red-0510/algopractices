// heap data structure
#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL)
#define fileio() freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#define ll long long int
#define forn(i,l,n) for(ll i=l;i<n;i++)

// all procedures
// 1) MAX_HEAPIFY(array,index)  maintaines heap property from ith index     O(lgn)
// 2) BUILDING_MAX_HEAP(array,n)  converts a array to heap                  O(nlgn)
// 3) HEAPSORT(array,n)         sorts an array                              O(nlogn)
// 4) HEAP_EXTRACT_MAX(array,n) return the maximum element in the heap and 
//                              maintains the heap property                 O(logn) for one call
// 5) HEAP_INCREASE_KEY(array,n,i,key) changes the key of array[i] and 
//                              maintains heap property                     O(logn)
// 6) HEAP_INSERT_KEY(array,n,key) inserts new element as key               O(logn)  
// 7) HEAP_DELETE(array,n,index)  deletes the node at index i and maintains 
//                                maintains heap property                   O(logn)                              

void printarr(vector<int>&);
void MAX_HEAPIFY(vector<int>& a,int i,int n){
    int l=2*i+1;
    int r=2*i+2;
    int largest=i;
    if (l<n && a[l]>a[i]){
        largest=l;
    }
    if(r<n && a[r]>a[largest]){
        largest=r;
    }
    if (largest!=i){
        swap(a[i],a[largest]);
        MAX_HEAPIFY(a,largest,n);
    }
}
void BUILD_MAX_HEAP(vector<int>& a,int n){
    for(int i=n/2;i>=0;i--){
        MAX_HEAPIFY(a,i,n);
    }
}
void HEAPSORT(vector<int> &a,int n){
    BUILD_MAX_HEAP(a,n);
    for(int i=(n-1);i>=1;i--){
        swap(a[i],a[0]);
        MAX_HEAPIFY(a,0,i);
    }
}
int HEAP_EXTRACT_MAX(vector<int> &a,int n){
    int max=a[0];
    a[0]=a[n-1];
    if (n>1){
        MAX_HEAPIFY(a,0,n-1);
    }
    return max;  
}
void HEAP_INCREASE_KEY(vector<int> &a,int n,int i,int key){
    a[i]=key;
    while(i>0 && a[(i-1)/2]<a[i]){
        swap(a[i],a[(i-1)/2]);
        i=(i-1)/2;
    }
}
void MAX_HEAP_INSERT(vector<int> &a,int n,int key){
    a.push_back(key);
    int i=n; 
    while(i>0 && a[(i-1)/2]<a[i]){
        swap(a[(i-1)/2],a[i]);
        i=(i-1)/2;
    }
}
void HEAP_DELETE(vector<int> &a,int n,int i){
    HEAP_INCREASE_KEY(a,n,i,a[0]+1);
    a[0]=a[n-1];
    a.pop_back();
    MAX_HEAPIFY(a,0,a.size());
}
void printarr(vector<int> &a){
    forn(i,0,a.size()){
        cout<<a[i]<<" ";
    }
    cout<<"\n";
}
int main(){
    freopen("output.txt","w",stdout);
    vector<int> a={5,4,-1,2,4,10,1};
    int s=a.size();
    // BUILD_MAX_HEAP(a,s);
    // for(int i=0;i<s;i++){
    //     cout<<HEAP_EXTRACT_MAX(a,s-i)<<" ";
    // }
    HEAPSORT(a,s);
    printarr(a);
    // HEAP_EXTRACT_MAX(a,s);
    // BUILD_MAX_HEAP(a,s);
    // printarr(a);
    // MAX_HEAP_INSERT(a,s,12);
    // // HEAP_INCREASE_KEY(a,s,3,10);
    // printarr(a);
    // HEAP_DELETE(a,a.size(),3);
    // printarr(a);
    return 0;
}