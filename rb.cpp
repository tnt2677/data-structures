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
void print_helper(const node *);
bool is_red(node*);
node* rotate_left(node*);
node* rotate_right(node*);
node* flip_color(node*);
node* insert_helper(node*,int);
bool find_helper(node*,const int);
int height_helper(node*);

class tree{
   private:
    node* root;
    int size;
   public:
    tree():root(NULL),size(0){}
    void insert(const int);
    void print(void)const;
    bool find(const int)const;
    int height()const;
};
int tree::height(void)const{
    return height_helper(this->root);
}
bool tree::find(const int key)const{
    return find_helper(this->root,key);
}
void tree::insert(const int key){
    this->root=insert_helper(this->root,key);
    if(is_red(this->root))this->root->color=black;
}
void tree::print(void)const{
    print_helper(root);
}
void print_helper(const node *root){
    if(!root)return;
    print_helper(root->left);
    cout<<root->data<<" ";
    print_helper(root->right);
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
node* insert_helper(node* root,int key){
    if(!root)return new node(key,red);
    
    if((root->data)>=key)root->left=insert_helper(root->left,key);
    else root->right=insert_helper(root->right,key);
    
    //cases for rb insertion
    if(is_red(root->right)&&!is_red(root->left))root=rotate_left(root);
    if(is_red(root->left)&&is_red(root->left->left))root=rotate_right(root);
    if(is_red(root->left)&&is_red(root->right))root=flip_color(root);
    return root;
}
bool find_helper(node* root,const int key){
    node* curr=root;
    while(curr){
        if(curr->data==key)return true;
        if(curr->data > key)curr=curr->left;
        else curr=curr->right;
    }
    return false;
}
int height_helper(node* root){
    if(!root)return 0;
    return max(height_helper(root->left),height_helper(root->right))+1;
}
int main(){
    
    return 0;
}
