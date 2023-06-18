#include <iostream>
#include "linked_list.hpp"

int main( void ) {
    List<int> list { 2,3,15,8,9,7,82,99,10 };
    List<int> lst { list };

    list[0] = 7;
    list[8] = 13;
    lst << 18;
    
    for ( auto i: list ) {
        std::cout << i  << " ";
    }

    std::cout << "\n";

    for ( auto& i: lst ) {
        std::cout << i  << " ";
    }
    
    return 0;
}