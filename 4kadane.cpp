#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL)
#define fileio() freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#define ll long long int
#define forn(l,n,i) for(ll i=l;i<n;i++)

pair<int,int> ispositive(int *a, int n){
    int res=a[0];
    int index=0;
    forn(0,n,i){
        if (a[i]>=0){
            return make_pair(-1,i);
        }
        else if(res<a[i]){
            res=a[i];
            index=i;
        }
    }
    return make_pair(1,index);
}
pair<int,int> kadane(int arr[],int n){
    int last_low=0,cur_low=0;
    int last_high=0;
    ll maxsum;
    int min,index;
    tie(min,index)=ispositive(arr,n);
    if (min==1) return make_pair(index,index);
    else {
        maxsum=arr[index];
        cur_low=index;
        last_low=index;
        last_high=index;
    }
    ll cursum=maxsum;
    int val;
    for (int i=cur_low+1;i<n;i++){
        if(cursum+arr[i]>=0) cursum+=arr[i];
        else{
            cursum=0;
            cur_low=i+1;
        }
        if (cursum>maxsum){
            last_high=i;
            last_low=cur_low;
            maxsum=cursum;
        }
    }
    return make_pair(last_low,last_high);
}
int main(){
    fileio();
    int n;
    cin>>n;
    int arr[n];
    for (int i=0;i<n;i++){
        cin>>arr[i];
    }
    auto v=kadane(arr,n);
    cout<<"start"<<v.first<<" "<<v.second<<"\n";
    for (int i=v.first;i<=v.second;i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}