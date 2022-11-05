// Radix Sort
// complexity:O(d*(n+k));d is no of digits ;n is number of elements to sort; k is number of possible values a digit can take i.e 10
// basic principle: it sorts the least significant digit of all the numbers and then proceeds further to sort the most dignificant digit 
// requirements: needs same amount of digits in all numbers
//              needs to use a stable sort in between (stable sort means that it maintains the respective order of equal elements as in which comes first)
//              stable sort egs:insertion sort, merge sort, counting sort 
//              nonstable sorts: heapsort, quicksort
//pseudocode:
// for i=1 to d:
//     use stable sort to sort the array based on the ith digit
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

void countsort(vector<int>& v,int d){
    vector<list<int>> lists(10);
    int n=v.size();
    forn(0,n,i){
        lists[(v[i]/d)%10].pb(v[i]);
    }
    int k=0;
    forn(0,lists.size(),i){
        for(int x:lists[i]){
            v[k]=x;
            k++;
        }
    }
}

void radixsort(vector<int>& v){
    int maxi=INT_MIN;
    for(int x:v) maxi=max(maxi,x);
    int i=1;
    while(maxi){
        countsort(v,i);
        maxi/=10;
        i*=10;
    }
}

void solve(){
    int n;
    cin>>n;
    vector<int> v(n);
    forn(0,n,i) cin>>v[i];
    radixsort(v);
    for(int x:v) cout<<x<<" ";
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