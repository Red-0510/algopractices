#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;

#define fastio() iosbase_::sync_with_stdio(false);cin.tie(NULL);
#define fileio() freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
#define ll long long int
#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define forn(l,n,i) for(ll i=l;i<n;i++) 

//HASH TABLES
//1)DIrect Address Tables: when range of keys are not to large 
//                         uses keys are index to store the data the key is mapping to
//                          to handle negative values use 2D array and consider 0->positive and 1->negative                                                        
struct PAIR{
    int key;
    int value;
};

class Hash{
    int BUCKET;
    vector<list<PAIR>> table;
    public:
        Hash(int size){
            this->BUCKET=size;
            table=vector<list<PAIR>>(size);
        }
        void hash_insert(int key,int value){
            PAIR p={key,value};
            key=hash_function(key);
            table[key].push_back(p); 
        }
        int hash_function(int key){
            return (key%this->BUCKET);
        }
        list<PAIR>::iterator operator[](int key){
            int hash=hash_function(key);
            cout<<"here"<<key<<endl;
            list<PAIR>::iterator i;
            for(i=table[hash].begin();i!=table[hash].end();i++){
                if (key==(*i).key) return i;
            }
            return i;
        }
        void hash_delete(int key){
            int hash=hash_function(key);
            list<PAIR>::iterator i;
            for(i=table[hash].begin();i!=table[hash].end();i++){
                if (key==(*i).key){
                    table[hash].erase(i);
                    return;
                }
            }
            cout<<"no such key:"<<key<<" found"<<endl;
        }
        void display_hash(){
            forn(0,this->BUCKET,i){
                list<PAIR>::iterator j;
                cout<<i<<"/--> ";
                for(j=this->table[i].begin();j!=this->table[i].end();j++){
                    cout<<(*j).key<<":"<<(*j).value<<" ---> ";
                }
                cout<<endl;
            }
        }
};
int main(){
    Hash *h=new Hash(7);
    h->hash_insert(3,13);
    h->hash_insert(4,14);
    h->hash_insert(5,15);
    h->hash_insert(6,16);
    h->hash_insert(12,22);
    h->display_hash();
    h->hash_delete(5);
    h->display_hash();
    return 0;
}