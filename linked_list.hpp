#include <iostream>
#include <string>
#include "node.hpp"
#include "Iterator.hpp"

template< typename T>
class List {
public:
  List() = default; 
  List( const List<T>& list );
  ~List();

  template< typename... Args>
  List( const T first, const Args... param );
  List( const T param );

  T& operator[] ( const uint32_t index );
  const T& operator[] ( const uint32_t index ) const;

  void operator<< ( const T param );
  void operator>> ( const T parma );

  Iterator<T> begin( void );
  Iterator<T> end( void );

  const Iterator<T> begin( void ) const;
  const Iterator<T> end( void ) const;

private:

  Node<T>* head_node ;
  Node<T>* tail_node ;
  uint32_t length {1};

};

template< typename T>
List<T>::List( const T param ) : 
  head_node{ new Node<T> { param, nullptr, tail_node } },
  tail_node{ head_node }
{}

template< typename T> 
template< typename... Args>
List<T>::List( const T first, const Args... param ):
  head_node{ new Node<T> { first, nullptr, nullptr } },
  length{ sizeof...( param ) + 1 }
{
  const T args_param[ sizeof...( param )] { std::move( param )... };
  Node<T>* tmp_head_node = head_node;
  for ( auto i : args_param ) {
    tmp_head_node->next_node = new Node<T> { i, tmp_head_node, nullptr };
    tmp_head_node = tmp_head_node->next_node; 
  }

  tail_node = tmp_head_node;
}

template< typename T> 
List<T>::List( const List<T>& list ): 
  head_node{ new Node<T> { list.head_node->values, nullptr, nullptr } } 
{
  if ( list.head_node->next_node == nullptr ) {
    ++length;
    return;
  }

  Node<T>* tmp { head_node };
  for ( Node<T>* i = list.head_node->next_node; i != nullptr; i = i->next_node ) {
    tmp->next_node = new Node<T> { i->values, tmp, nullptr };
    tmp = tmp->next_node;
    ++length;
  }

  tail_node = tmp;
}

template< typename T>
List<T>::~List() {
  Node<T>* tmp { tail_node };
  tail_node = tmp->prev_node;

  delete tmp;

  this->~List();
}

template< typename T> 
T& List<T>::operator[] ( const uint32_t index  ) {
  if ( index > this->length - 1 ) throw " out of range";
  if ( index == 0) return head_node->values;
  if ( index == this->length - 1) return tail_node->values;

  Node<T>* tmp_head_node { head_node };

  for ( uint32_t i=0; i < index; ++i ) {
    tmp_head_node = tmp_head_node->next_node;
  }

  return tmp_head_node->values; 
} 

template< typename T> 
const T& List<T>::operator[] ( const uint32_t index  ) const {
  if ( index > this->length - 1 ) throw " out of range";
  if ( index == 0) return head_node->values;
  if ( index == this->length - 1) return tail_node->values;

  Node<T>* tmp_head_node { head_node };

  for ( uint32_t i=0; i < index; ++i ) {
    tmp_head_node = tmp_head_node->next_node;
  }

  return tmp_head_node->values; 
} 

template< typename T>
void List<T>::operator<< ( const T param ) {
  length += 1;
  Node<T>* tmp { tail_node };

  tmp->next_node = new Node<T> { param, tmp, nullptr };
  tail_node = tmp->next_node;
}

template< typename T>
void List<T>::operator>> ( const T param ) {

  if ( param == tail_node->values ) {
    Node<T>* tmp { tail_node };

    tail_node = tail_node->prev_node;
    delete tmp;
    --length;
    return;
  }

  Node<T>* tmp_prev;
  Node<T>* tmp { head_node };
  for ( ; tmp != nullptr; tmp = tmp->next_node ) {
    if ( tmp->values == param ) {
      tmp_prev = tmp->prev_node;
      tmp_prev->next_node = tmp->next_node;
      tmp->next_node->prev_node = tmp_prev;
      delete tmp;
    }
  }

  --length;
}

template< typename T>
Iterator<T> List<T>::begin( void ) {
  return Iterator{ head_node };
} 

template< typename T> 
Iterator<T> List<T>::end( void ) {
  return Iterator{ tail_node->next_node };
}

template< typename T>
const Iterator<T> List<T>::begin( void ) const {
  return Iterator{ head_node };
} 

template< typename T> 
const Iterator<T> List<T>::end() const {
  return Iterator{ tail_node->next_node };
}
