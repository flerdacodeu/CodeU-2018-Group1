template <typename T>
LinkedList<T>::LinkedList()
{
    _preHead = new Node<T>;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    Node<T>* current = _preHead;
    Node<T>* next;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
}

template <typename T>
void LinkedList<T>::addElementToEnd(const T &value)
{
    Node<T>* current = _preHead;
    while (current->next != nullptr)
        current = current->next;
    Node<T>* end = new Node<T>();
    end->value = value;
    current->next = end;
}

template <typename T>
size_t LinkedList<T>::size()
{
    size_t cnt = 0;
    Node<T>* current = _preHead;
    while (current->next != nullptr) {
        current = current->next;
        cnt++;
    }
    return cnt;
}

template <typename T>
Node<T>* LinkedList<T>::kth_from_last(size_t k) {
    size_t size = this->size();

    if (k + 1 > size)
        throw std::out_of_range("k should be less than LinkedList size");

    size_t offset = size - k - 1;

    Node<T>* current = _preHead;
    while (offset) {
        offset -= 1;
        current = current->next;
    }

    return current->next;
}