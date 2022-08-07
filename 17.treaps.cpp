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

struct Node{
    int key,priority;
    Node *left,*right,*parent;
};
// Treap : Balanced Binary search tree
// Properties:
// each node consites of pair of a key and a priority
//  1) keys are arranged as in a regular BST
//  2) priorities follow either max-heap / min-heap property i.e.min-heap: parent is lesser lesser than child(not necessary smaller is left and bigger is right)
class MinTreap{ // with min-Heap property
    int N=100;
    public:
        Node* root,*nil;

        MinTreap(){
            this->nil=new Node();
            this->nil->left=NULL;
            this->nil->right=NULL;
            this->nil->parent=NULL;
            this->root=this->nil;
        }
        // generates a randomly unique priority integer
        int priorityGenerator(){
            return rand()%this->N;
        }

        void leftRotate(Node* x){
            Node* y=x->right;
            x->right=y->left;       
            if(y->left!=NULL) y->left->parent=x;
            y->parent=x->parent;
            if(x->parent==this->nil){
                this->root=y;
            }
            else if(x==x->parent->left){
                x->parent->left=y;
            }
            else x->parent->right=y;
            y->left=x;
            x->parent=y;
        }
        //assumes that left child of x in not nil
        void rightRotate(Node* x){
            Node* y=x->left;
            x->left=y->right;       
            if(y->right!=this->nil) y->right->parent=x;
            y->parent=x->parent;
            if(x->parent==this->nil){
                this->root=y;
            }
            else if(x==x->parent->left){
                x->parent->left=y;
            }
            else x->parent->right=y;
            y->right=x;
            x->parent=y;
        }

        Node* search(int key){
            Node* x=this->root;
            while(x!=this->nil){
                if(x->key==key) return x;
                else if(x->key<key) x=x->right;
                else x=x->left;
            }
            return x;
        }

        Node* getMin(Node* x){
            while(x->left!=this->nil){
                x=x->left;
            }
            return x;
        }

        void transplant(Node* u,Node* v){
            if(u->parent==this->nil){
                this->root=v;
                return;
            }
            else if(u==u->parent->left) u->parent->left=v;
            else u->parent->right=v;
            if(v!=this->nil) v->parent=u->parent;
        }

        // insertion is regular as normal BST
        // after inserting the node at its position as per the BST property
        // the tree is balanced by maintaining the heap property on the priority values of nodes
        void Treap_insert(int key){
            Node * temp=new Node();
            Node* y=this->nil;
            Node* x=this->root;
            while(x!=this->nil){
                y=x;
                if(x->key>key) x=x->left;
                else x=x->right;
            }
            if(y==this->nil){
                this->root=temp;
            }
            else if(key>y->key) y->right=temp;
            else y->left=temp;
            temp->parent=y;
            temp->key=key;
            temp->priority=this->priorityGenerator();
            temp->left=this->nil;
            temp->right=this->nil;

            // now mainting the heap property by travelling up the ancestor and checking that the heap property is satisfied
            // y is the parent and temp is the node inserted
            while(y!=this->nil && y->priority>temp->priority){
                // CASE 1: when temp is left child we right rotate
                if (temp==y->left) this->rightRotate(y);
                //CASE 2: when temp is the right child of y we left rotate
                else if(temp==y->right) this->leftRotate(y);
                y=temp->parent;
            }
        }
        // delete a node in Treap
        // 1) if node is leaf simply delete
        // 2) if node has only child replace the node with that child and delete the node
        // 3) if node has both childs then rotate it with the appropriate child as per the heap-property ( key idea is to flow this node down to leaf)
        void Treap_delete(Node *x){
            Node *y=this->nil;
            if(x==this->nil)return ;
            while(x->left!=this->nil || x->right!=this->nil){
                // left child is nil
                if(x->left==this->nil){
                    y=x->right;
                    break ;
                }
                // right child is nil
                else if(x->right==this->nil){
                    y=x->left;
                    break;
                }
                // both childs are present
                else{
                    if(x->left->priority < x->right->priority)this->rightRotate(x);
                    else this->leftRotate(x);
                }
            }
            this->transplant(x,y);
        }

        void printTree(Node *x){
            vector<Node*>v;
            v.pb(x);
            vector<Node*>temp;
            while(v.size()){
                temp.clear();
                forn(0,v.size(),i){
                    cout<<"("<<" "<<v[i]->key<<","<<v[i]->priority<<")   ";
                    if(v[i]->left!=this->nil)temp.pb(v[i]->left);
                    if(v[i]->right!=this->nil)temp.pb(v[i]->right);
                }
                cout<<endl;
                v=temp;
            }
        }
};

int main(){

    MinTreap trp;
    trp.Treap_insert(50);
    trp.Treap_insert(30);
    trp.Treap_insert(20);
    trp.Treap_insert(40);
    trp.Treap_insert(70);
    trp.Treap_insert(60);
    trp.Treap_insert(80);
    trp.printTree(trp.root);
    Node *el=trp.search(60);
    trp.Treap_delete(el);
    trp.printTree(trp.root);
    return 0;
}