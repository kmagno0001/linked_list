#include "node.hpp"

template< typename T>
class Iterator {
public:
    Iterator( Node<T>* node );

    Iterator& operator++ ( void );
    T& operator* ();
    bool operator!= ( const Iterator<T>& iter ) const;

private:
    Node<T>* iterator_node;
};

template< typename T>
Iterator<T>::Iterator( Node<T>* node ): 
    iterator_node{ node }
{}

template< typename T>
Iterator<T>& Iterator<T>::operator++ ( void ){
    iterator_node = iterator_node->next_node;
    return *this;
}

template< typename T> 
T& Iterator<T>::operator* ( void ) {
    return iterator_node->values;
}

template< typename T>
bool Iterator<T>::operator!= ( const Iterator<T>& iter ) const {
    return  iterator_node != iter.iterator_node;
}