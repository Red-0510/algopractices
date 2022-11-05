#include<iostream>

using namespace std;
void merge(int arr[],int p,int q,int r);
void printarr(int arr[],int n){
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<"\n";
}
void merge_sort(int arr[],int p,int r){
    if(p<r){
        int q=(p+r)/2;
        merge_sort(arr,p,q);  //dividing subarrays by 2
        merge_sort(arr,q+1,r);
        merge(arr,p,q,r);
    }
}
void merge(int arr[],int p,int q,int r){
    // cout<<p<<q<<r<<"\n";
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
    int arr[9]={5,6,4,3,2,5,7,18,9};
    int n=9;  
    merge_sort(arr,0,n-1);
    printarr(arr,n);
    return 0;
}