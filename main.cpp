#include <iostream>
#include "linked_list.hpp"

int main( void ) {
    List<int> list { 2,3,15,8,9,7,82,99,10 };
    List<int> lst { list };

    list[0] = 7;
    list[8] = 13;
    list >> 3;
    lst << 18;
    
    for ( auto i: list ) {
        std::cout << i  << " ";
    }

    std::cout << "\n";

    for ( auto i: lst ) {
        std::cout << i  << " ";
    }

    std::cout << "\n";

    for ( auto i = lst.begin(); i != lst.end(); ++i ) {
        std::cout << *i  << " ";
    }

    std::cout << "\n";
    lst << 9;
    
    for ( auto i = lst.begin(); i != lst.end(); i++ ) {
        std::cout << *i  << " ";
    }

    std::cout << "\n";

    for ( auto i = lst.rbegin(); i != lst.rend(); --i ) {
        std::cout << *i  << " ";
    }
    
    std::cout << "\n";

    for ( auto i = lst.rbegin(); i != lst.rend(); i-- ) {
        std::cout << *i  << " ";
    }

    std::cout << "\n";
    
    return 0;
}