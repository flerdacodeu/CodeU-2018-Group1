#include <cstdio>

template <typename T>
struct Node {
    Node() : next(nullptr) { }

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
    void addElementToEnd(const T& value);
    Node<T> *kth_from_last(size_t k);

protected:
    Node<T>* _preHead;
};
