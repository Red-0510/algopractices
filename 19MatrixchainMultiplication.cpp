//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++

class Solution{
public:
    int matrixMultiplication(int n, int arr[])
    {
        int m[n][n];
        vector<vector<int>> s(n-1,vector<int>(n-1));
        for(int i=0;i<n;i++){
            m[i][i]=0;
        }
        int i,j,k,q;
        for(int len=2;len<n;len++){
            for(i=1;i<(n-len+1);i++){
                j=i+len-1;
                m[i][j]=INT_MAX;
                for(k=i;k<j;k++){
                    q=m[i][k]+m[k+1][j]+arr[i-1]*arr[k]*arr[j];
                    if(m[i][j]>q){
                        m[i][j]=q;
                        s[i-1][j-1]=k;
                    }
                    // m[i][j]=min(m[i][j],m[i][k]+m[k+1][j]+arr[i-1]*arr[k]*arr[j]);
                }
            }
        }
        this->output(s,0,n-2);
        cout<<endl;
        return m[1][n-1];
        
    }

    void output(vector<vector<int>>& v,int i,int j){
        if(i==j){
            cout<<"A"<<i+1;
        }
        else{
            cout<<" (";
            output(v,i,v[i][j]-1);
            output(v,v[i][j],j);
            cout<<")";
        }
    }
};

//{ Driver Code Starts.

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t;
    cin>>t;
    while(t--){
        int N;
        cin>>N;
        int arr[N];
        for(int i = 0;i < N;i++)
            cin>>arr[i];
        
        Solution ob;
        cout<<ob.matrixMultiplication(N, arr)<<endl;
    }
    return 0;
}