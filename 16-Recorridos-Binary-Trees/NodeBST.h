#ifndef _NODEBST_H_
#define _NODEBST_H_

template <class T>
class NodeBST {
  private:
    T data;
    NodeBST<T> *left;
    NodeBST<T> *right;

  public:
    NodeBST();
    NodeBST(T value);
    // El template BST<U> tiene acceso a los elementos privados de esta clase
    template<typename U> friend class BST;

};

template <class T>
NodeBST<T>::NodeBST() : data {}, left(nullptr), right(nullptr) {}

template <class T>
NodeBST<T>::NodeBST(T value) : data {value}, left(nullptr), right(nullptr) {}

#endif // _NODEBST_H_