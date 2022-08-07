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

// Red Black Trees:height balancing BST
// properties:all peopreties of a BST
//  1)all nodes are red or black
//  2) root is always black
//  3)every nil is black
//  4)no consecutive red nodes
//  5) any simple path from a node to nil has same number of black nodes
struct Node{
    int key;
    int color;// 0-black 1-red
    Node *left,*right,*parent;
};

class redBlackTree{
    public:
        Node* root;
        Node* nil;
        redBlackTree(){
            this->nil=new Node();
            this->nil->color=0;
            this->nil->left=NULL;
            this->nil->right=NULL;
            this->nil->parent=NULL;
            this->root=this->nil;
            // this->root->parent=this->nil;
        }
        // assuming that the right child of x node is not nil
        void leftRotate(Node* x){
            Node* y=x->right;
            x->right=y->left;       
            if(y->left!=this->nil) y->left->parent=x;
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

        // RB inserts a node with key k in the RB tree and then calls the RB fixup to maintain the properties that might have been violated by inserting the node

        void RB_insert(int key){
            Node* temp=new Node();
            Node* y=this->nil;
            Node* x=this->root;
            while(x!=this->nil){
                y=x;
                if(x->key>key){
                    x=x->left;
                }
                else x=x->right;
            }
            temp->parent=y;
            if(y==this->nil){
                this->root=temp;
            }
            else if(key<y->key) y->left=temp;
            else y->right=temp;
            temp->left=this->nil;
            temp->right=this->nil;
            temp->key=key;
            temp->color=1;
            this->RB_insert_fixup(temp);
        }
        // to handle the required rotations and recoloring after inserting a node to maintain the properties of the red black trees
        void RB_insert_fixup(Node* z){
            while(z->parent->color==1){
                // considering a z parent to be a left child
                if(z->parent==z->parent->parent->left){
                    // y is uncle
                    Node* y=z->parent->parent->right;
                    //CASE 1:Unclde of z is RED  =>only change color and travel two level up to check for any other violation of properties
                    if(y->color==1){
                        z->parent->color=0;
                        y->color=0;
                        z->parent->parent->color=1;
                        z=z->parent->parent;// as the grandparent color is now red loop body is continued
                    }

                    else{
                        // CASE 2:Uncle is black and z is left child 
                        //we first left rotate to convert to CASE 3 and then
                        if(z==z->parent->right){
                            z=z->parent;
                            this->leftRotate(z);
                        }
                        // CASE 3: Uncle is black and z is right child
                        // we right rotate and color of parent and grandparent and as the grand parent color is now black loop body will terminate on next iteration
                        z->parent->color=0;
                        z->parent->parent->color=1;
                        this->rightRotate(z->parent->parent);
                    }
                }
                // considering z->parent to be right child
                else{
                    // y is uncle
                    Node* y=z->parent->parent->left;
                    //CASE 1:Unclde of z is RED  =>only change color and travel two level up to check for any other violation of properties
                    if(y->color==1){
                        z->parent->color=0;
                        y->color=0;
                        z->parent->parent->color=1;
                        z=z->parent->parent;// as the grandparent color is now red loop body is continued
                    }

                    else{
                        // CASE 2:Uncle is black and z is left child 
                        //we first left rotate to convert to CASE 3 and then
                        if(z==z->parent->left){
                            z=z->parent;
                            this->rightRotate(z);
                        }
                        // CASE 3: Uncle is black and z is right child
                        // we right rotate and color of parent and grandparent and as the grand parent color is now black loop body will terminate on next iteration
                        z->parent->color=0;
                        z->parent->parent->color=1;
                        this->leftRotate(z->parent->parent);
                    }
                }
            }
            this->root->color=0;
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

        void printTree(Node *x){
            vector<Node*>v;
            v.pb(x);
            vector<Node*>temp;
            while(v.size()){
                temp.clear();
                forn(0,v.size(),i){
                    cout<<"("<<" "<<v[i]->key<<","<<v[i]->color<<")   ";
                    if(v[i]->left!=this->nil)temp.pb(v[i]->left);
                    if(v[i]->right!=this->nil)temp.pb(v[i]->right);
                }
                cout<<endl;
                v=temp;
            }
        }

        // trnasplant similar as BST transplant to replace subtree u with subtree v
        void RB_transplant(Node* u,Node* v){
            if(u->parent==this->nil)this->root=v;
            else if(u==u->parent->left) u->parent->left=v;
            else u->parent->right=v;
            v->parent=u->parent;
        }
        // to delete a node from a RBT similar to BST delete and calls delete_fixup as the displaced node y's color can cause violation of RBT properties
        void RB_delete(Node* z){
            Node* y=z,*x;
            int y_original_color=y->color;
            if(z->left==this->nil){
                x=z->right;
                this->RB_transplant(z,z->right);
            }
            else if(z->right==this->nil){
                x=z->left;
                this->RB_transplant(z,z->left);
            }
            else{
                y=this->getMin(z->right);
                y_original_color=y->color;
                x=y->right;
                if(y->parent==z) x->parent=y;
                else{
                    this->RB_transplant(y,y->right);
                    y->right=z->right;
                    y->right->parent=y;
                }
                RB_transplant(z,y);
                y->left=z->left;
                y->left->parent=y;
                y->color=z->color;
            }
            if(y_original_color==0) this->RB_delete_fixup(x);
        }
        // maintains the properties of a RBT involves 4 cases:
        // CASE1 canoverts to case 2,3,4
        // case 2 continues the loop
        // case 3 converts to case 4
        // case 4 uses 1 left/right rotate and loop exits
        void RB_delete_fixup(Node* x){
            // node x represents doubly black node(i.e if we consider the contribution of node x as 2 black nodes than black height property of RBT is conserved) 
            // hence we try to convert this doubly black node to single black node
            Node *w;
            while(x!=this->root && x->color==0){
                // considering x as a left child
                if(x==x->parent->left){
                    w=x->parent->right;// w is sibling of x
                    // CASE1: w is red
                    if(w->color==1){
                        w->color=0;
                        x->parent->color=1;
                        this->leftRotate(x->parent);
                        w=w->parent->right;
                    }
                    // CASE 2: w is black and both w's children are black
                    if(w->left->color==0 && w->right->color==0){
                        w->color=1;
                        x=x->parent;
                    }
                    else{
                        // CASE 3: w is black and w's right child is black
                        if(w->right->color==0){
                            w->left->color=0;
                            w->color=1;
                            this->rightRotate(w);
                            w=x->parent->right;
                        }
                        //CASE 4: w is black and w's right child is red
                        w->color=x->parent->color;
                        x->parent->color=0;
                        w->right->color=0;
                        this->leftRotate(x->parent);
                        x=this->root;// this will exit the loop
                    }
                }
                // considering x as a right child
                else{
                    w=x->parent->left;// w is sibling of x
                    // CASE1: w is red
                    if(w->color==1){
                        w->color=0;
                        x->parent->color=1;
                        this->rightRotate(x->parent);
                        w=w->parent->left;
                    }
                    // CASE 2: w is black and both w's children are black
                    if(w->left->color==0 && w->right->color==0){
                        w->color=1;
                        x=x->parent;
                    }
                    else{
                        // CASE 3: w is black and w's left child is black
                        if(w->right->color==0){
                            w->right->color=0;
                            w->color=1;
                            this->leftRotate(w);
                            w=x->parent->left;
                        }
                        //CASE 4: w is black and w's left child is red
                        w->color=x->parent->color;
                        x->parent->color=0;
                        w->left->color=0;
                        this->rightRotate(x->parent);
                        x=this->root;// this will exit the loop
                    }
                }
            }
            x->color=0;
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

};
int main(){
    redBlackTree rbt;
    rbt.RB_insert(41);
    rbt.RB_insert(38);
    rbt.RB_insert(31);
    rbt.RB_insert(12);
    rbt.RB_insert(19);
    rbt.RB_insert(8);
    rbt.RB_insert(38);
    rbt.printTree(rbt.root);

    Node* el=rbt.search(8);
    
    rbt.RB_delete(el);
    rbt.printTree(rbt.root);
    cout<<"-----"<<endl;
    el=rbt.search(12);
    rbt.RB_delete(el);
    rbt.printTree(rbt.root);
    cout<<"-----"<<endl;
    el=rbt.search(19);
    rbt.RB_delete(el);
    rbt.printTree(rbt.root);
    cout<<"-----"<<endl;
    el=rbt.search(31);
    rbt.RB_delete(el);
    rbt.printTree(rbt.root);
    cout<<"-----"<<endl;
    el=rbt.search(38);
    rbt.RB_delete(el);
    rbt.printTree(rbt.root);
    cout<<"-----"<<endl;
    el=rbt.search(41);
    rbt.RB_delete(el);
    rbt.printTree(rbt.root);
    cout<<"-----"<<endl;
    cout<<rbt.root->key<<" "<<rbt.root->parent<<" "<<rbt.nil<<endl;
    return 0;
}