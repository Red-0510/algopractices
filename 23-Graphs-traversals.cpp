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

class Node{
    public:
    list<int> nbrs;
    int node;
    int distance;
    Node(int n){
        node=n;
        distance=0;
    }

    void add(int y){
        nbrs.pb(y);
    }
};

class Graph{
    int V;
    vector<Node*> graph;
    public:  
    Graph(int v){
        V=v;
        graph=vector<Node*>(V);
        forn(0,V,i){
            graph[i]=new Node(i);
        }
    }
    void add_edge(int x,int y,bool dir=false){
        graph[x]->add(y);
        if(!dir) graph[y]->add(x);
    }

    void printgraph(){
        forn(0,V,i){
            cout<<graph[i]->node<<"--> ";
            for(int x:graph[i]->nbrs) cout<<x<<", ";
            cout<<endl;
        }
    }

    void bfs(int source,int dest=-1){
        queue<int> q;
        vector<bool> visited(V,false);
        vector<int> parent(V);
        parent[source]=source;
        graph[source]->distance=0;
        visited[source]=true;
        q.push(source);
        while(!q.empty()){
            cout<<q.front()<<" ";
            for(int nbr:graph[q.front()]->nbrs){
                if(!visited[nbr]){
                    q.push(nbr),visited[nbr]=true;
                    parent[nbr]=q.front();
                    graph[nbr]->distance=graph[q.front()]->distance+1;
                } 
            }
            q.pop();
        }
        cout<<endl;
        for(auto x:graph){
            cout<<"Distance of "<<x->node<<" "<<x->distance<<" "<<endl;
        }
        if(dest!=-1){
            while(dest!=source){
                cout<<dest<<" ";
                dest=parent[dest];
            }
            cout<<source<<endl;
        }
    }

    void dfs(int source,vector<bool>& visited){
        visited[source]=true;
        cout<<source<<" ";
        for(int nbr:graph[source]->nbrs){
            if(!visited[nbr]) dfs(nbr,visited);
        }
    }

    void dfs(int source){
        vector<bool> visited(V,false);
        dfs(source,visited);
    }
    
};

int main(){
    fileio();
    int nodes=7;
    Graph g(nodes);
    g.add_edge(1,0);
    g.add_edge(1,2);
    g.add_edge(2,3);
    g.add_edge(0,4);
    g.add_edge(3,4);
    g.add_edge(3,5);
    g.add_edge(4,5);
    g.add_edge(5,6);
    // g.printgraph();
    g.bfs(1,6);
}