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


// BINARY SEARCH TREES 
// properties:
//      1)all keys in left sutree are less than parent and all nodes in right
//          sub tree are greater than the parent.
// Procedures
//  a)INsertion Node                        O(h)
//  b)deletion Node                         O(h)
//  c)getMin/getMAx                         O(h)
//  d)inordertraversal                      O(n) n->nodes in BST
//  e)search                                O(h)
//  f)sucessor/predecessor                  O(h)
//  g)transplant                            o(1)
// Node contains key,left child and right child
struct Node{
    int key;
    Node *left,*right,*parent;
};
// The BST Object
class BST{
    public:
        Node* root;
        BST(){
            this->root=NULL;
        }
        void insertNode(int key){
            Node* temp=new Node();
            temp->key=key;
            Node *y,*x;
            y=NULL;
            x=this->root;
            while(x!=NULL){
                y=x; 
                if(x->key<key){
                    x=x->right;
                }
                else x=x->left;
            }
            temp->parent=y;
            if(y==NULL){
                this->root=temp;
            }
            else if(y->key<key){
                y->right=temp;
            }
            else y->left=temp;
        }

        void inorderPrint(Node* x){
            if(x!=NULL){
                inorderPrint(x->left);// preordertraversal: x -->left -->right
                cout<<x->key<<" ";    // inorder:           let-->x-->right
                inorderPrint(x->right);// post order  left-->right-->x
            }
        }
        Node* search(int key){
            Node* x=this->root;
            while(x!=NULL){
                if(x->key==key) return x;
                else if(x->key<key) x=x->right;
                else x=x->left;
            }
            return x;
        }

        Node* getMin(Node* x){
            while(x->left!=NULL){
                x=x->left;
            }
            return x;
        }
        Node* getMax(Node* x){
            while(x->right!=NULL){
                x=x->right;
            }
            return x;
        }
        Node* successor(Node* x){
            if(x->right!=NULL) return getMin(x->right);// x has a right subtree
            Node* y=x->parent;// if no right subtree than the successor will   be ancestor of x such that is hs a left subtree
            while(y!=NULL && x==y->right){
                x=y;
                y=y->parent;
            }
            return y;
        }

        Node* predecessor(Node* x){
            if(x->left!=NULL) return getMax(x->left);
            Node* y=x->parent;
            while(y!=NULL && x==y->left){
                x=y;
                y=y->parent;
            }
            return y;
        }
        // replaces subtreee rooted at node u ,
        // with subtree rooted at v assuming v is independent here
        void transplant(Node* u,Node* v){
            if(u->parent==NULL){
                this->root=v;
                return;
            }
            else if(u==u->parent->left) u->parent->left=v;
            else u->parent->right=v;
            if(v!=NULL) v->parent=u->parent;
        }
        // deletes the node in BST 4 cases
        void deleteNode(Node* x){
            // first two to handle cases when both child are NULL or any one child is NULL
            if(x==NULL) return;
            if(x->left==NULL) this->transplant(x,x->right);
            else if(x->right==NULL) this->transplant(x,x->left);
            // here it consists of both childs we find successor(x) and replace x with it.
            else{
                Node* y=this->getMin(x->right);
                if(y->parent!=x){
                    this->transplant(y,y->right);
                    y->right=x->right;
                    y->right->parent=y;
                }
                this->transplant(x,y);
                y->left=x->left;
                y->left->parent=y;
            }
        }

        void leftRotate(Node* x){
            Node* y=x->right;
            x->right=y->left;       
            if(y->left!=NULL) y->left->parent=x;
            y->parent=x->parent;
            if(x->parent==NULL){
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
            if(y->right!=NULL) y->right->parent=x;
            y->parent=x->parent;
            if(x->parent==NULL){
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
            int j=50;
            vector<Node*>v;
            v.pb(x);
            vector<Node*>temp;
            while(v.size()){
                temp.clear();
                forn(0,v.size(),i){
                    cout<<v[i]->key<<"    ";
                    if(v[i]->left!=NULL)temp.pb(v[i]->left);
                    if(v[i]->right!=NULL)temp.pb(v[i]->right);
                    j-=2;
                }
                cout<<endl;
                v=temp;
            }
        }

};

int main(){
    BST bst;
    bst.insertNode(4);
    bst.insertNode(8);
    bst.insertNode(-10);
    bst.insertNode(12);
    bst.insertNode(1);
    bst.insertNode(0);
    bst.insertNode(-10);
    bst.insertNode(3);
    bst.insertNode(5);
    bst.inorderPrint(bst.root);
    cout<<endl;
    bst.printTree(bst.root);
    // Node* el=bst.search(-10);
    // bst.leftRotate(el);
    // bst.printTree(bst.root);
    // // cout<<"\n"<<el->key<<" "<<el->left->key<<" "<<el->right->key<<" "<<endl<<el->parent->key;
    // // cout<<bst.getMax(bst.root)->key<<" "<<bst.getMin(bst.root)->key<<endl;
    // bst.deleteNode(el);
    // bst.inorderPrint(bst.root);
    // cout<<endl;
    return 0;
}