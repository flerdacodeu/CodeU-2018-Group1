#include <array>
#include <vector>
#include <iostream>

template<typename T, size_t N = 2>
struct Node
{
    T value;
    std::array<Node<T>*, N> children;

    Node(const T value, std::array<Node<T>*, N> children)
            : value(value), children(children)
    { }

    bool find(const T& target, std::vector<Node*>& path)
    {
        if (value == target)
            return true;

        for (Node<T>* child : children)
        {
            if (child != nullptr && child->find(target, path))
            {
                path.push_back(this);
                return true;
            }
        }

        return false;
    }
};

int main()
{
    Node<int>* root = new Node<int>(7, {
            new Node<int>(3, {
                    new Node<int>(2, {
                            new Node<int>(1, {}), new Node<int>(6, {})
                    }),
                    new Node<int>(5, {})
            }),
            new Node<int>(4, {
                    new Node<int>(6, {}),
                    new Node<int>(8, {})
            })
    });

    std::vector<Node<int>*> result;
    root->find(6, result);

    for (auto node : result)
        std::cout << node->value << ' ';
}