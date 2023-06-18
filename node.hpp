#pragma once

template <typename T >
struct Node {
    T values;
    Node<T>* prev_node { nullptr };
    Node<T>* next_node { nullptr };
}; 
