#include <cstdio>

template <typename T>
struct Node {
    Node() : next(nullptr) { }
    Node(T value) : value(value), next(nullptr) { }

    T value;
    Node* next;
};


template <typename T>
class LinkedList {

public:
    LinkedList();
    ~LinkedList();

public:
    size_t size();
    void Append(const T &value);
    Node<T> *KthFromLast(size_t k);

protected:
    // This linked list implementation stores the preHead node because it helps with working with empty list
    Node<T>* _preHead;
};
