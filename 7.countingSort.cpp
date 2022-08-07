
// counting Sort
// basic principle: counts number of elements less than or equal to i from o to k; where k is the largest value in the set
// complexity: O(n) in avg case when value of k is less
// cons: cant be used for large difference in values ed 10,000
//      only works for integers for 0 to k;

#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL)
#define fileio() freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#define ll long long int
#define forn(l,n,i) for(ll i=l;i<n;i++)
#define pb push_back
void printarr(vector<int>&);
vector<int>CountingSort(vector<int>& a,int k){
    vector<int> c(k+1,0);
    forn(0,a.size(),i){
        c[a[i]]+=1;
    }
    forn(1,c.size(),i){
        c[i]=c[i]+c[i-1];
    }
    vector<int> b(a.size(),0);
    for(int i=a.size()-1;i>=0;i--){
        b[c[a[i]]-1]=a[i];
        c[a[i]]--;
    }
    return b;
}
void printarr(vector<int> &a){
    forn(0,a.size(),i){
        cout<<a[i]<<" ";
    }
    cout<<"\n";
}

int main(){
    vector<int> a={5,6,3,7,2,8,5};
    int s=a.size();
    printarr(a);
    vector<int> b=CountingSort(a,8);
    printarr(b);
    return 0;
}