#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL)
#define fileio() freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#define ll long long int
#define pb push_back
#define pf push_front
#define ppf pop_front
#define ppb pop_back
#define forn(l,n,i) for(ll i=l;i<n;i++)

// BINOMIAL HEAPS
// properties:
// 1.A binomial heap of n nodes has log(n) Binomial trees
// 2.the degrees of binomial trees in a binomial heap of n nodes can be related to binary representation of number n
//         eg. Binomial heap of 13 nodes has 1 tree of order 3,2,0 i.e 2^3+2^2+2^0=13 or 13~1101
// 3.every binomial tree follows min heap/maxheap property
// 4.there cant be two binomial trees of same degree in a binomial heap. if there are they are merged to form binomial tree of order i+1
// OPERATIONS:
// 1)Creation of heap(cretaing a empty linked list)                 O(1)
// 2)Insertion node                                                 O(logn)
// 3)getting minimum elements                                       O(logn)
// 4)Extract minimimu key (removing from the heap)                  O(logn)
// 5)Union or merge Operation                                       O(logn)
// 6)Decreasing a key                                               O(logn)
// 7)Deleting a node                                                O(logn) 
struct Node{
    int data,degree;
    Node *child,*parent,*sibling;
};

Node* newNode(int data){
    Node* node=new Node();
    node->data=data;
    node->degree=0;
    node->parent=node->child=node->sibling=NULL;
    return node;
}

// function to merge two binomial trees
Node* mergeBinomialTrees(Node* b1,Node* b2){
    if(b1->data>b2->data){
        swap(b1,b2);
    }
    b2->parent=b1;
    b2->sibling=b1->child;
    b1->child=b2;
    b1->degree++;
    return b1;
}

// union operation for two binomial heap
//this function unites two binomial trees according to increasing order of their degree
list<Node*> unionBinomialHeap(list<Node*> l1,list<Node*> l2){
    list<Node*> new_list; //new list after the union operation
    list<Node*>::iterator it1=l1.begin();
    list<Node*>::iterator it2=l2.begin();
    while(it1!=l1.end() && it2!=l2.end()){
        if(((*it1)->degree<=(*it2)->degree)){
            new_list.pb(*it1);
            it1++;
        }
        else{
            new_list.pb(*it2);
            it2++;
        }
    }
    while(it1!=l1.end()){
        new_list.pb(*it1);
        it1++;
    }
    while(it2!=l2.end()){
        new_list.pb(*it2);
        it2++;
    }
    return new_list;
}

list<Node*> adjust_heap(list<Node*> heap){
    if(heap.size()<=1) return heap;
    list<Node*>::iterator it1,it2,it3;
    it1=it2=it3=heap.begin();
    if(heap.size()==2){
        // it2=it1;
        it2++;
        it3=heap.end();
    }
    else{
        it2++;
        it3=it2;
        it3++;
    }
    while(it1!=heap.end()){
        if(it2==heap.end()){//case1 if it1 is pointing to last element we are done
            it1++;
        }
        else if((*it1)->degree<(*it2)->degree){// if degree of next tree is greater than current tree we continue
            it1++;
            it2++;
            if(it3!=heap.end()) it3++;
        }
        else if(it3!=heap.end() && (*it1)->degree==(*it2)->degree && (*it1)->degree==(*it3)->degree){// if D(current)==D(next)==D(next->next) we conitnue
            it1++;                                                                                   // so that in future we can merge D(next) and D(next->next)
            it2++;
            it3++;
        }
        else if((*it1)->degree==(*it2)->degree){// if D(current)==D(next) merge these two trees
            *it1=mergeBinomialTrees(*it1,*it2);
            it2=heap.erase(it2);
            if(it3!=heap.end()) it3++;
        }
    }
    return heap;
}
list<Node*> insertTreeinBinomialHeap(list<Node*> heap,Node* tree){
    list<Node*> new_heap;
    new_heap.pb(tree);
    new_heap=unionBinomialHeap(heap,new_heap);
    return adjust_heap(new_heap);
}

list<Node*> insert(list<Node*> heap,int data){
    Node* node=newNode(data);
    return insertTreeinBinomialHeap(heap,node);
}

void printTree(Node* head){
    while(head){
        cout<<head->data<<" ";
        printTree(head->child);
        head=head->sibling;
    }
}
void printHeap(list<Node*> heap){
    list<Node*>::iterator it=heap.begin();
    while(it!=heap.end()){
        cout<<"[ ";
        printTree(*it);
        it++;
        cout<<"]";
    }
    cout<<endl;
}
Node* get_Min(list<Node*> heap){
    list<Node*>::iterator it=heap.begin();
    Node* temp=*it;
    while(++it!=heap.end()){
        if((*it)->data<temp->data) temp=*it;
    }
    return temp;
}
list<Node*> remove_root(Node* key){
    list<Node*> child_list;
    Node* temp=key->child;
    Node* temp2;
    while(temp){
        temp2=temp;
        temp=temp->sibling;
        temp2->sibling=NULL;
        child_list.pf(temp2);
    }
    return child_list;
}
list<Node*> extract_Min(list<Node*> heap){
    Node* min=get_Min(heap);
    list<Node*> new_heap,child_list;
    list<Node*>::iterator it=heap.begin();
    while(it!=heap.end()){
        if((*it)!=min) new_heap.pb(*it);
        it++;
    }
    child_list=remove_root(min);
    new_heap=unionBinomialHeap(new_heap,child_list);
    return adjust_heap(new_heap);
}
list<Node*> remove_node(list<Node*> heap,Node* node){
    list<Node*> new_heap,child_list;
    list<Node*>::iterator it=heap.begin();
    while(node->parent){
        swap(node->data,node->parent->data);
        node=node->parent;
    }
    while(it!=heap.end()){
        if((*it)!=node) new_heap.pb(*it);
        it++;
    }
    child_list=remove_root(node);
    new_heap=unionBinomialHeap(new_heap,child_list);
    return adjust_heap(new_heap);
}
void printNode(Node* node){
    cout<<node<<" "<<node->data<<" "<<node->degree<<" "<<node->child<<" "<<node->parent<<endl;
}
int main(){
    list<Node*> heap;
    heap=insert(heap,10);
    heap=insert(heap,20);
    heap=insert(heap,-1);
    heap=insert(heap,10);
    heap=insert(heap,5);
    printHeap(heap);
    cout<<get_Min(heap)->data;
    heap=extract_Min(heap);
    printHeap(heap);
    auto min=get_Min(heap);
    heap=remove_node(heap,min->child->child);
    printHeap(heap);
    cout<<get_Min(heap)->data;
    heap=extract_Min(heap);
    printHeap(heap);
    cout<<get_Min(heap)->data;
    heap=extract_Min(heap);
    printHeap(heap);
    cout<<get_Min(heap)->data;
    heap=extract_Min(heap);
    printHeap(heap);
}
