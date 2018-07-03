# Data-Structures

_Contains implementation of frequently used data structures :-_
    
   ### 1.Left Leaning Red-Black Trees( tree.h ):
   
        * void insert(key)
        * size_t size(void)
        * unsigned int height(void)
        * void print(void)
        * bool find(key)
   
   ### 2.Order-Statistics Tree( order_tree.h ):
   _the given utilities work in _O_( log<sub>2</sub> n ) and use "0" based indexing_
   
        * data get_kth(K) : returns kth order-statitics if valid, else largest element 
        * int get_order(key) : returns order of the element if present, else returns -1
        * void insert(key)
        * size_t size(void)
        * bool find(key)
   
