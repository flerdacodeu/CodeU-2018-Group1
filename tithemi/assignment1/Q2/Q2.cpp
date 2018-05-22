#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "Q2_linked_list.h"
#include "Q2_linked_list.hpp"

int main()
{
    LinkedList<int> list;

    list.addElementToEnd(1);
    list.addElementToEnd(2);
    list.addElementToEnd(3);
    list.addElementToEnd(4);

    std::cout << list.kth(0)->value << std::endl; // 4
    std::cout << list.kth(1)->value << std::endl; // 3
    std::cout << list.kth(2)->value << std::endl; // 2
    std::cout << list.kth(3)->value << std::endl; // 1
    return 0;
}
