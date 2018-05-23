#include <bits/stdc++.h>
using namespace std;

const bool red=true;
const bool black=false;

struct node{
    int data;
    node* left;
    node* right;
    bool color;//color of parent link
    //default & parametrized constructor
    node(int data=0,bool color=red):data(data),left(NULL),right(NULL),color(color){}
};
class tree{
   private:
    node* root;
    int size;
   public:
    tree():root(NULL),size(0){}
    friend node* insert(int);
    friend void print(node*);
};
void print(node *root){
    if(!root)return;
    print(root->left);
    cout<<root->data<<" ";
    print(root->right);
}
bool is_red(node* curr){
    //null links are black
    if(!curr)return false;
    //return if red
    return curr->color==red;
}
node* rotate_left(node* curr){
    //rotate a right leaning link,say x 
    assert(is_red(curr->right));
    node* x = curr->right;
    curr->right=x->left;
    x->left=curr;
    x->color=curr->color;
    curr->color=red;
    return x;
}
node* rotate_right(node* curr){
    //rotate a left leaning link to right
    assert(is_red(curr->left));
    node* x = curr->left;
    curr->left=x->right;
    x->right=curr;
    x->color=curr->color;
    curr->color=red;
    return x;
}
node* flip_color(node* curr){
    //assert(!is_red(curr));
    //assert(is_red(curr->left));
    //assert(is_red(curr->right));
    curr->right->color=black;
    curr->left->color=black;
    curr->color=red;
    return curr;
}
node* insert(node* root,int key){
    if(!root)return new node(key,red);
    
    if((root->data)>=key)root->left=insert(root->left,key);
    else root->right=insert(root->right,key);
    
    //cases for rb insertion
    if(is_red(root->right)&&!is_red(root->left))root=rotate_left(root);
    if(is_red(root->left)&&is_red(root->left->left))root=rotate_right(root);
    if(is_red(root->left)&&is_red(root->right))root=flip_color(root);
    return root;
}
node* find(node* root,int key){
    node* curr=root;
    while(curr){
        if(curr->data==key)return curr;
        if(curr->data > key)curr=curr->left;
        else curr=curr->right;
    }
    return NULL;
}
int height(node* root){
    if(!root)return 0;
    return max(height(root->left),height(root->right))+1;
}
int main(){
    node* root=NULL;
    root=new node(50,black);
    for(int i=0;i<10;++i){root=insert(root,i);if(is_red(root))root->color=black;cout<<i<<endl;}
    return 0;
}
