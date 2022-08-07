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

// AVL Trees : height balancing BST
// properties: all properties of a BST
//  1)| h.left - h.right |<=1 at any node.

struct Node{
    int key,height;
    Node* parent,*left,*right;
};
class AVLTree{
    public:
        Node* root,*nil;
        
        AVLTree(){
            this->root=NULL;
            this->nil=new Node();
            this->nil->height=0;
            this->nil->left=NULL;
            this->nil->right=NULL;
            this->nil->parent=NULL;
            this->root=this->nil;
        }

        void AVL_insert(int key){
            Node* temp=new Node();
            Node* y=this->nil;
            Node*x=this->root;
            while(x!=this->nil){
                y=x;
                if(x->key<key)x=x->right;
                else x=x->left;
            }
            if(y==this->nil) this->root=temp;
            else if(key<y->key){
                y->left=temp;
                if(y->right==this->nil)y->height=1;
            }
            else{
                y->right=temp;
                if(y->left==this->nil) y->height=1;
            }
            temp->parent=y;
            temp->height=1;
            temp->right=this->nil;
            temp->left=this->nil;
            temp->key=key;
            // updates height trvaersing upwards from node inserted and balances the ree by rotation
            int balance;
            Node *z;
            // get the first unbalanced node z and rotations will be performed only on this node as other ancestors remains unchanged 
            // z--->y--->x as three nodes can be arranged in 4 ways we have four cases z is the first unbalanced node
            // finding the firsr unvalanced node
            while(y!=this->nil){
                balance=y->left->height - y->right->height;
                if(balance >1 || balance<-1)break;
                y->height=1+max(y->left->height,y->right->height);
                y=y->parent;
            }
            if(y!=this->nil){
                // CASE 1: Left left 
                if(balance>1 && key<y->left->key){
                    this->rightRotate(y);
                }
                // CASE 2: left right 
                else if(balance>1 && key > y->left->key){
                    z=y->left;
                    this->leftRotate(y->left);
                    z->height=1+max(z->left->height,z->right->height);
                    this->rightRotate(y);
                }
                // CASE 3: right right
                else if( balance<-1 && key>y->right->key){
                    this->leftRotate(y);
                }
                //CASE 4:right left
                else if(balance<-1 && key<y->right->key){
                    z=y->right;
                    this->rightRotate(y->right);
                    z->height=1+max(z->left->height,z->right->height);
                    this->leftRotate(y);
                }
                y->height=1+max(y->left->height,y->right->height);
                y->parent->height=1+max(y->parent->left->height,y->parent->right->height);
            }
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
        void printTree(Node *x){
            vector<Node*>v;
            v.pb(x);
            vector<Node*>temp;
            while(v.size()){
                temp.clear();
                forn(0,v.size(),i){
                    cout<<"("<<" "<<v[i]->key<<","<<v[i]->height<<")   ";
                    if(v[i]->left!=this->nil)temp.pb(v[i]->left);
                    if(v[i]->right!=this->nil)temp.pb(v[i]->right);
                }
                cout<<endl;
                v=temp;
            }
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
        Node* getMax(Node* x){
            while(x->right!=this->nil){
                x=x->right;
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

        void AVL_delete(Node *z){
            Node *y;
            if(z==this->nil) return ;
            else if(z->left==this->nil){
                y=z->right;
                this->transplant(z,y);
            }
            else if(z->right==this->nil) {
                y=z->left;
                this->transplant(z,y);
            }
            else{
                // regular BST deletion
                y=this->getMin(z->right);
                if(y->parent!=z){
                    this->transplant(y,y->right);
                    y->right=z->right;
                    y->right->parent=y;
                }
                this->transplant(z,y);
                y->left=z->left;
                y->left->parent=y;
            }
            //BALANCING the AVL 
            Node *a=y;
            int balance;
            Node *b,*c;
            while(a!=this->nil){
                balance=a->left->height - a->right->height;
                if(balance>1 || balance<-1){
                    b=(a->left->height < a->right->height)?a->right:a->left;
                    c=(b->left->height < b->right->height)?b->right:b->left;
                    // b is big height child of a and
                    // c is big height chihld of b
                    // CASE 1 : left left
                    if(balance>1 && c->key<b->key) this->rightRotate(a);
                    //CASE 2:left right
                    else if(balance>1 && c->key>b->key){
                        this->leftRotate(b);
                        b->height=1+max(b->left->height,b->right->height);
                        this->rightRotate(a);
                    }
                    // CASE 3:right right
                    else if(balance<-1 && c->key>b->key)this->leftRotate(a);
                    //CASE 4 :right left
                    else if(balance<-1 && c->key<b->key){
                        this->rightRotate(b);
                        b->height=1+max(b->left->height,b->right->height);
                        this->leftRotate(a);
                    }
                }
                a->height=1+max(a->left->height,a->right->height);
                a=a->parent;
            }
        }
};
int main(){
    AVLTree avt;
    avt.AVL_insert(9);
    avt.AVL_insert(5);
    avt.AVL_insert(10);
    avt.AVL_insert(0);
    avt.AVL_insert(6);
    avt.AVL_insert(11);
    avt.AVL_insert(-1);
    avt.AVL_insert(1);
    avt.AVL_insert(2);
    avt.printTree(avt.root);
    Node *el=avt.search(10);
    avt.AVL_delete(el);
    avt.printTree(avt.root);
    return 0;
}