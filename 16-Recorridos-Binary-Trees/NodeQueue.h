#ifndef _NODEQUEUE_H_
#define _NODEQUEUE_H_

template <class T>
class NodeQueue {
  private:
    T data;
    NodeQueue<T> *next;

  public:
    NodeQueue();
    NodeQueue(T value);
    // El template QueueLL<U> tiene accesso a las variables de clase privadas de esta clase
    template<typename U> friend class QueueLL;   
};

template <class T> 
NodeQueue<T>::NodeQueue() : data{}, next{nullptr} {}

template <class T> 
NodeQueue<T>::NodeQueue(T value) : data{value}, next{nullptr} {}


#endif // _NODEQUEUE_H_