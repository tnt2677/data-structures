#include <iostream>
#include<assert.h>

#ifndef TREE_H
#define TREE_H

const bool red=true;
const bool black=false;

template<typename T>
struct node{
    T data;
    node* left;
    node* right;
    bool color;//color of parent link

    //default & parametrized constructor
    node(T data=0,bool color=red):data(data),left(NULL),right(NULL),color(color){}
    ~node(){}
};

template<typename T>
class tree{
   private:
    node<T>* root;
    unsigned int Size;
   public:
    tree():root(NULL),Size(0){}
    virtual ~tree();//to make sure if a derived class is present it's destructor is called first

    //function decleration
    void insert(const T);
    void print(void)const;
    bool find(const T)const;
    int height()const;
    unsigned int size()const{return Size;}
};

template<typename T>
void print_helper(const node<T> *);
template<typename T>
bool is_red(node<T>*);
template<typename T>
node<T>* rotate_left(node<T>*);
template<typename T>
node<T>* rotate_right(node<T>*);
template<typename T>
node<T>* flip_color(node<T>*);
template<typename T>
node<T>* insert_helper(node<T>*,T);
template<typename T>
bool find_helper(node<T>*,const T);
template<typename T>
int height_helper(node<T>*);
template<typename T>
bool is_leaf(const node<T>*);

template<typename T>
tree<T>::~tree(){
    delete_tree(this->root);
    Size=0;
}

template<typename T>
bool is_leaf(const node<T>* curr){
    if(!curr)return false;
    return ((!curr->left)&&(!curr->right));
}

template<typename T>
void delete_tree(node<T>* root){
    if(!root)return;
    if(is_leaf(root)){
        delete(root);
        return;
    }
    delete_tree(root->left);
    delete_tree(root->right);
    root->right=root->left=NULL;
    delete(root);
}

template<typename T>
int tree<T>::height(void)const{
    return height_helper(this->root);
}

template<typename T>
bool tree<T>::find(const T key)const{
    return find_helper(this->root,key);
}

template<typename T>
void tree<T>::insert(const T key){
    this->root=insert_helper(this->root,key);
    if(is_red(this->root))this->root->color=black;
    Size++;
}

template<typename T>
void tree<T>::print(void)const{
    print_helper(root);
}

template<typename T>
void print_helper(const node<T> *root){
    if(!root)return;
    print_helper(root->left);
    std::cout<<root->data<<" ";
    print_helper(root->right);
}

template<typename T>
bool is_red(node<T>* curr){
    //null links are black
    if(!curr)return false;
    //return if red
    return curr->color==red;
}

template<typename T>
node<T>* rotate_left(node<T>* curr){
    //rotate a right leaning link,say x
    assert(is_red(curr->right));
    node<T>* x = curr->right;
    curr->right=x->left;
    x->left=curr;
    x->color=curr->color;
    curr->color=red;
    return x;
}

template<typename T>
node<T>* rotate_right(node<T>* curr){
    //rotate a left leaning link to right
    assert(is_red(curr->left));
    node<T>* x = curr->left;
    curr->left=x->right;
    x->right=curr;
    x->color=curr->color;
    curr->color=red;
    return x;
}

template<typename T>
node<T>* flip_color(node<T>* curr){
    assert(!is_red(curr));
    assert(is_red(curr->left));
    assert(is_red(curr->right));
    curr->right->color=black;
    curr->left->color=black;
    curr->color=red;
    return curr;
}

template<typename T>
node<T>* insert_helper(node<T>* root,T key){
    if(!root)return new node<T>(key,red);

    if((root->data)>=key)root->left=insert_helper(root->left,key);
    else root->right=insert_helper(root->right,key);

    //cases for rb insertion
    if(is_red(root->right)&&!is_red(root->left))root=rotate_left(root);
    if(is_red(root->left)&&is_red(root->left->left))root=rotate_right(root);
    if(is_red(root->left)&&is_red(root->right))root=flip_color(root);
    return root;
}

template<typename T>
bool find_helper(node<T>* root,const T key){
    node<T>* curr=root;
    while(curr){
        if(curr->data==key)return true;
        if(curr->data > key)curr=curr->left;
        else curr=curr->right;
    }
    return false;
}

template<typename T>
int height_helper(node<T>* root){
    if(!root)return 0;
    return std::max(height_helper(root->left),height_helper(root->right))+1;
}

#endif // TREE_H
