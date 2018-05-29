#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "Q2_linked_list.h"
#include "Q2_linked_list.hpp"

int main()
{
    LinkedList<int> list;

    list.Append(1);
    list.Append(2);
    list.Append(3);
    list.Append(4);

    std::cout << list.KthFromLast(0)->value << std::endl; // 4
    std::cout << list.KthFromLast(1)->value << std::endl; // 3
    std::cout << list.KthFromLast(2)->value << std::endl; // 2
    std::cout << list.KthFromLast(3)->value << std::endl; // 1
    // std::cout << list.KthFromLast(4)->value << std::endl; // out_of_range exception
    return 0;
}
