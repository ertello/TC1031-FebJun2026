#ifndef _NODEAVL_H_
#define _NODEAVL_H_

template <class T>
class NodeAVL {
  private:
    T data;
    NodeAVL<T> *left;
    NodeAVL<T> *right;
    int height;

  public:
    NodeAVL();
    NodeAVL(T value);
    // El template AVLTree<U> tiene acceso a los elementos privados de esta clase
    template<typename U> friend class AVLTree;

};

template <class T>
NodeAVL<T>::NodeAVL() : data {}, left(nullptr), right(nullptr), height{1} {}

template <class T>
NodeAVL<T>::NodeAVL(T value) : data {value}, left(nullptr), right(nullptr), height{1} {}

#endif // _NODEAVL_H_