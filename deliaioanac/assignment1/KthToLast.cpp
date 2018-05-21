#include <iostream>
#include <stdlib.h>

using namespace std;

template <class T>
struct ListNode {
    T data;
    struct ListNode *next;
};

template <typename T>
T getKthToLast(ListNode<T> *head, int k) {
    // Sanity check
    if (k < 0) {
        cerr << "getKthToLast: k must be a positive number!" << endl;
        exit(EXIT_FAILURE);
    }

    ListNode<T> *follower = head;

    // Move the head up by k positions
    // (the follower will be left behind by k positions so that,
    //  when the head reached the end of the list, the follower is
    //  on the kth to last element)
    while (head != NULL && k > 0) {
        head = head->next;
        k --;
    }

    // If the head is NULL, it means there were less than k elements
    // in the list, so we can not find the kth to last element
    if (head == NULL) {
        cerr << "getKthToLast: Not enough elements!" << endl;
        exit(EXIT_FAILURE);
    }

    // Move both pointers until the head reached the end of the list and,
    // as explained, the follower will be on the kth to last element
    while (head != NULL && head->next != NULL) {
        head = head->next;
        follower = follower->next;
    }

    return follower->data;
}
