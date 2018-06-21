#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

struct node {
    node *ancestor = nullptr;
    node *left = nullptr;
    node *right = nullptr;
    int value;
};

// The algorithm works as follows:
//  1. Raises the nodes up by the power of 2 steps and if they encounter it means that first node originally higher than second on 'distance'.
//  2. If then don't encounter swap first and second nodes and if they encounter it means that second node originally higher the first on 'distance'.
//  3. If they do not collide, increase the power of two.
//  4. Repeat this steps while we don't find common node. If the nodes have a common ancestor, they must someday collide.
//  5. Then we raise the bottom node by 'distance'.
//  6. And then raise both node until they collide in the lowest common ancestor.

//  And it works of O(height of lowest common ancestor -  height of lower node). 
//  Because 2^1 + 2^2 + .. + 2^(n-1) = 2^n where 2^n >= (height of lowest common ancestor -  height of lower node) >= 2^(n-1).

//The function raises nodes several steps up
//Returns: -1 -- nodes did not collide  or  (up_on - cnt) -- the difference between the height of the first and second node, if the nodes collided.
//In this program up_on = power_of_two
int collided_or_not (node *first, node*second, const int up_on) {
    int cnt = 0;
    while (first != nullptr && cnt != up_on) {
        first = first->ancestor;
        cnt++;
    }
    cnt = 0;
    while (second != nullptr && cnt != up_on) {
        if (second == first) {
            return up_on - cnt;
        }
        second = second->ancestor;
        cnt++;
    }
    return -1;
}

node *LowestCommonAncestor(node *first, node *second) {
    if (first == nullptr || second == nullptr) return nullptr;
    int power_of_two = 1;
    int distance;
    while (1) {
        distance = collided_or_not(first, second, power_of_two);
        if (distance != -1) break;
        distance = collided_or_not(second, first, power_of_two);
        if (distance != -1) {
            //It is necessary to swap
            //Because probably the second vertex is higher than the first one and then the vertex will not collide when the first function was called.
            std::swap(first, second);
            break;
        }
        //We increase the power of two.
        power_of_two *= 2;
    }
    //Raise the lower vertex to the height of the top
    while (distance > 0) {
        first = first->ancestor;
        distance--;
    }
    //Raise until the vertex collide in the LCA
    while (first != second) {
        first = first->ancestor;
        second = second->ancestor;
    }
    return first;
}
