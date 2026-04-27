#ifndef _NODESPLAYTREE_H_
#define _NODESPLAYTREE_H_

#include <iostream>

template <class T>
class NodeSplayTree { 
public: 
    T data; 
    NodeSplayTree<T>* left;
    NodeSplayTree<T>* right;
    NodeSplayTree();
    NodeSplayTree(T value);
}; 

template<class T>
NodeSplayTree<T>::NodeSplayTree() : data{}, left{nullptr}, right{nullptr} {}

template<class T>
NodeSplayTree<T>::NodeSplayTree(T value) : data{value}, left{nullptr}, right{nullptr} {}

#endif // _NODESPLAYTREE_H_