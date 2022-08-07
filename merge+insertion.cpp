#include<iostream>
#include<bits/stdc++.h>
using namespace std;
void merge(int arr[],int p,int q,int r);
void printarr(int arr[],int n){
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<"\n";
}
void insertion_sort(int arr[],int p,int r){
    int key,j;
    for (int i = p; i <=r; i++){
        key=arr[i];
        j=i-1;
        while (j>=p && arr[j]>key){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}
void merge_sort(int arr[],int p,int r,int k){
    if ((r-p)<=(k)){
        insertion_sort(arr,p,r);
    }
    else if(p<r){
        int q=(p+r)/2;
        merge_sort(arr,p,q,k);  //dividing subarrays by 2
        merge_sort(arr,q+1,r,k);
        merge(arr,p,q,r);
    }
}
void merge(int arr[],int p,int q,int r){
    int n1=q-p+1;
    int n2=r-q;
    int L[n1];
    int R[n2];
    for (int i = 0; i < n1; i++){
        L[i]=arr[p+i];
    }
    for (int i = 0; i < n2; i++){
        R[i]=arr[q+i+1];
    }
    int i=0;
    int j=0;
    int k=p;
    while(i<n1 && j<n2){
        if (L[i]<=R[j]){
            arr[k]=L[i];
            i++;
        }
        else {
            arr[k]=R[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        arr[k]=L[i];
        i++;
        k++;
    }
    while(j<n2){
        arr[k]=R[j];
        j++;
        k++;
    }
}
int main(){ 
    freopen("output.txt","w",stdout);
    int arr[9]={5,2,4,3,2,5,7,18,9};
    int n=9;
    int k=3;
    vector<int> v(arr,arr+n);
    merge_sort(arr,0,n-1,k);
    printarr(arr,n);
    sort(v.begin(),v.end());
    for (auto i=v.begin();i!=v.end();i++) cout<<*i<<" ";
    return 0;
}