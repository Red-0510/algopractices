#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL)
#define fileio() freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#define ll long long int
#define forn(l,n,i) for(ll i=l;i<n;i++)

// Doubly Linked List using sentinels

class Node {
    public:
        int data;
        Node* next;
        Node* prev;
        Node(){data=-1;next=NULL;prev=NULL;}
        Node(int data){this->data=data;next=NULL;prev=NULL;}
};

class LINKED_LIST {
    public:
        Node* head;
        ll size;
        LINKED_LIST(){
            this->head=new Node();//sentinel
            this->size=0;
        }
        void insert_Node(int data){
            Node* x=new Node(data);
            if (!this->head->next){
                this->head->next=x;
                this->head->prev=x;
                x->next=this->head;
                x->prev=this->head;
            }
            else{
                x->next=this->head->next;
                x->prev=this->head;
                this->head->next->prev=x;
                this->head->next=x;
            }
            this->size++;
        }

        Node* search(int k){
            Node* x=this->head->next;
            while(x!=this->head && x->data!=k){
                x=x->next;
            }
            return x;
        }

        void print_list(){
            Node* x=this->head->next;
            while(x!=this->head){
                cout<<"( "<<x->data<<" "<<x->prev->data<<" "<<x->next->data<<") \n";
                x=x->next;
            }
            cout<<"\n";
        }
        void delete_Node(int k){
            Node* x=search(k);
            if (x==this->head)cout<<"No corresponding value found ";
            else{
                x->next->prev=x->prev;
                x->prev->next=x->next;
            }
        }
};

int main(){
    LINKED_LIST* LL = new LINKED_LIST();
    forn(0,5,i){
        LL->insert_Node(i);
    }
    LL->print_list();
    LL->delete_Node(4);
    LL->print_list();
    return 0;
}
