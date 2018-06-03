#include <iostream>
#include <stdlib.h>
#include <vector>

template <class T>
struct ListNode {
    T data;
    ListNode *next;
    ListNode(T x) : data(x), next(nullptr) {} 
};

template <class T>
class CustomList {
    private:
        ListNode<T> *head = nullptr;
    public:
        // Adds the element to the list
        void addElement(T data) {
            ListNode<T> *new_head = new ListNode<T>(data);
            
            if (!new_head) {
                std::cerr << "new failed" << std::endl;
                return;

            }

            new_head->next = head;
            head = new_head;
        }

        // Adds all the elements to the list
        void addElements(const std::vector<T> &elements) {
            for (T elem : elements) {
                addElement(elem);
            }
        }

        // Destroys the entire list
        void destroyList() {
            while (head) {
                ListNode<T> *aux = head->next;
                delete head;
                head = aux;
            }
        }

        T getKthToLast(int k) {
            // Sanity check
            if (k < 0) {
                throw std::out_of_range("index must be a positive number");
            }

            ListNode<T> *follower = head;
            ListNode<T> *leader = head;

            // Move the head up by k positions
            // (the follower will be left behind by k positions so that,
            //  when the head reached the end of the list, the follower is
            //  on the kth to last element)
            while (leader != nullptr && k > 0) {
                leader = leader->next;
                k --;
            }

            // If the head is NULL, it means there were less than k elements
            // in the list, so we can not find the kth to last element
            if (leader == nullptr) {
                throw std::out_of_range("index is too high");
            }

            // Move both pointers until the head reached the end of the list and,
            // as explained, the follower will be on the kth to last element
            while (leader != nullptr && leader->next != nullptr) {
                leader = leader->next;
                follower = follower->next;
            }

            return follower->data;
        }
};
