#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL)
#define fileio() freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#define ll long long int

tuple<int,int,ll> max_crossarray(int arr[],int l,int m,int r){
    ll left_sum=arr[m];
    ll sum=arr[m];
    int left=m;
    for (int i=m-1;i>=l;i--){
        sum+=arr[i];
        if (sum>=left_sum){
            left_sum=sum;
            left=i;
        }
    }
    ll right_sum=0;
    sum=0;
    int right=m;
    for (int i=m+1;i<=r;i++){
        sum+=arr[i];
        if (sum>=right_sum){
            right_sum=sum;
            right=i;
        }
    }
    return make_tuple(left,right,left_sum+right_sum);
}
tuple<int,int,ll> max_subarray(int arr[],int l,int r){
    if (l==r){
        return make_tuple(l,r,arr[l]);
    }
    int m=(l+r)/2;
    auto left=max_subarray(arr,l,m);
    auto right=max_subarray(arr,m+1,r);
    auto cross=max_crossarray(arr,l,m,r);
    if (get<2>(left)>get<2>(right) && get<2>(left)>get<2>(cross)) return left;
    else if (get<2>(cross)>get<2>(right) && get<2>(cross)>get<2>(left)) return cross;
    else if (get<2>(right)>get<2>(left) && get<2>(right)>get<2>(cross)) return right;
    else {
        if ((get<1>(left)-get<0>(left)+1)>=(get<1>(right)-get<0>(right)+1) && (get<1>(left)-get<0>(left)+1)>=(get<1>(cross)-get<0>(cross)+1)) return left;
        else if ((get<1>(cross)-get<0>(cross)+1)>=(get<1>(right)-get<0>(right)+1) && (get<1>(cross)-get<0>(cross)+1)>=(get<1>(left)-get<0>(left)+1)) return cross;
        return right;
    }
}
int main(){
    fileio();
    int n;
    cin>>n;
    int arr[n];
    for (int i=0;i<n;i++){
        cin>>arr[i];
    }
    // for (int i=0;i<n;i++){
    //     cout<<arr[i]<<" ";
    // }
    auto v=max_subarray(arr,0,n-1);
    // cout<<get<0>(v)<<" "<<get<1>(v)<<" "<<get<2>(v);
    for (int i=get<0>(v);i<=get<1>(v);i++){//correct 3 8 5 11 14 17
        cout<<arr[i]<<" ";
    }
    return 0;
}