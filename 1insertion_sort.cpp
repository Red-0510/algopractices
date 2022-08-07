#include<iostream>

using namespace std;
void insertion_sort(int arr[],int n){
    int key,j;
    for (int i = 1; i <n; i++){
        key=arr[i];
        j=i-1;
        while (j>=0 && arr[j]>key){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}
int main(){ 
    int arr[9]={5,6,4,3,2,5,7,18,9};
    int n=9;  
    insertion_sort(arr,n);
    return 0;
}