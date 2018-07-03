//class order tree
#include <iostream>
#include<assert.h>

#ifndef ORDER_TREE_H
#define ORDER_TREE_H

const bool red = true;
const bool black = false;

template<typename T>
struct node{
    T data;
    node* left;
    node* right;
    int sz;//number of values smaller than current node
    bool color;//color of parent link
    //default & parametrized constructor
    node(T data = 0,bool color = red):data(data),left(NULL),right(NULL),color(color),sz(1){}
    ~node(){}
};

template<typename T>
class order_tree{
   private:
    node<T>* root;
    std::size_t Size;
   public:
    order_tree():root(NULL),Size(0){}
    virtual ~order_tree();//to make sure if a derived class is present it's destructor is called first

    ///function declaration:
    //insertion:-
    void insert(const T);
    //find:-
    bool find(const T)const;
    //returns order of element in tree:-
    int get_order(const T)const;
    //size:-
    std::size_t size()const{return Size;}
    //isEmpty:-
    bool empty(void)const{return (int)Size == 0;};
    //return's kth element:-
    T get_kth(int k)const;
};

template<typename T>
T _get_kth(const node<T> *,int);
template<typename T>
int get_size(const node<T> *);
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
void set_size(node<T>* &curr);

//*********************************************************************************************************************************************//
//destructor for the tree and helper function:-

template<typename T>
order_tree<T>::~order_tree(){
    delete_tree(this->root);
    Size = 0;
}

template<typename T>
void delete_tree(node<T>* root){
    if(!root)return;
    if(!root->left&&!root->right){
        delete(root);
        return;
    }
    delete_tree(root->left);
    delete_tree(root->right);
    root->right=root->left = NULL;
    delete(root);
}

//*********************************************************************************************************************************************//
//get size utility:-

template<typename T>
int get_size(const node<T>* curr){
    if(!curr)return 0;
    return (curr->sz);
}

//*********************************************************************************************************************************************//
//returns kth order statistic:-

template<typename T>
T order_tree<T>::get_kth(int k)const{
    if(k >= this->Size)k = this->Size-1;
    return _get_kth(this->root,k);
}

template<typename T>
T _get_kth(const node<T>* root,int k){
    //0 based indexing
    int n = get_size(root->left);
    if(n == k)return root->data;
    if(n > k)return _get_kth(root->left,k);
    return _get_kth(root->right,k-n-1);
}

//*********************************************************************************************************************************************//
//find function:-

template<typename T>
bool order_tree<T>::find(const T key)const{
    node<T>* curr = this->root;
    while(curr){
        if(curr->data == key)return true;
        if(curr->data > key)curr=curr->left;
        else curr = curr->right;
    }
    return false;
}

//*********************************************************************************************************************************************//
//returns order statistics of an element O(log n) time:-
//get_kth and wrapper function:-

template<typename T>
int order_tree<T>::get_order(const T key)const{
    node<T>* curr = this->root;
    int ans = 0;
    while(curr){
        if(curr->data == key)return ans;
        if(curr->data > key)curr=curr->left;
        else {
            ans+=get_size(curr->left)+1;
            curr = curr->right;
        }
    }
    return -1;
}
//*********************************************************************************************************************************************//
//size updation utility:-

template<typename T>
void set_size(node<T>* &curr){
    if(!curr)return;
    curr->sz = 1 + get_size(curr->right) + get_size(curr->left);
}

//*********************************************************************************************************************************************//
// rotate functions and balancing utilites:-

template<typename T>
bool is_red(node<T>* curr){
    //null links are black
    if(!curr)return false;
    //return if red
    return curr->color == red;
}

template<typename T>
node<T>* rotate_left(node<T>* curr){
    //rotate a right leaning link,say x
    assert(is_red(curr->right));
    node<T>* x = curr->right;
    
    curr->right = x->left;
    x->left = curr;
    
    x->color = curr->color;
    curr->color = red;
    
    //now update size
    set_size(x->left);
    set_size(x->right);
    set_size(x);
    
    return x;
}

template<typename T>
node<T>* rotate_right(node<T>* curr){
    //rotate a left leaning link to right
    assert(is_red(curr->left));
    node<T>* x = curr->left;
    curr->left = x->right;
    x->right = curr;
    x->color = curr->color;
    curr->color = red;
    
    //now update size
    set_size(x->left);
    set_size(x->right);
    set_size(x);
    
    return x;
}

template<typename T>
node<T>* flip_color(node<T>* curr){
    assert(!is_red(curr));
    assert(is_red(curr->left));
    assert(is_red(curr->right));
    curr->right->color=black;
    curr->left->color=black;
    curr->color = red;
    return curr;
}

//*********************************************************************************************************************************************//
//insert function and wrapper function:-

template<typename T>
void order_tree<T>::insert(const T key){
    this->root = insert_helper(this->root,key);
    
    //make sure root is black
    if(is_red(this->root))this->root->color=black;
    Size++;
}

template<typename T>
node<T>* insert_helper(node<T>* root,T key){
    //if root is NULL done!!
    if(!root)return new node<T>(key,red);
    
    //if curr data is greater than we are inserting in it's left sub-tree
    if((root->data) >= key)root->left = insert_helper(root->left,key);
    else root->right = insert_helper(root->right,key);

    //cases for rb insertion
    if(is_red(root->right) && !is_red(root->left))root = rotate_left(root);
    if(is_red(root->left) && is_red(root->left->left))root = rotate_right(root);
    if(is_red(root->left) && is_red(root->right))root = flip_color(root);
    
    //update size of curr node
    set_size(root);
    
    return root;
}
//*********************************************************************************************************************************************//

#endif // ORDER_TREE_H
