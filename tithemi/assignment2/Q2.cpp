#include <array>
#include <vector>
#include <iostream>

template<typename T, size_t N = 2>
struct Node
{
    T value;
    std::array<Node<T, N>*, N> children;

    Node(const T value, std::array<Node<T, N>*, N> children)
            : value(value), children(children)
    { }

    bool find(const T& target, std::vector<Node<T, N>*>& path)
    {
        if (value == target)
            return true;

        for (Node<T, N>* child : children)
        {
            if (child != nullptr && child->find(target, path))
            {
                path.push_back(this);
                return true;
            }
        }

        return false;
    }

    Node<T, N>* findCommon(const T& first, const T& second)
    {
        std::vector<Node<T, N>*> firstPath, secondPath;

        if (!find(first, firstPath) || !find(second, secondPath))
            return nullptr;

        auto firstIt = firstPath.rbegin();
        auto secondIt = secondPath.rbegin();

        do
        {
            firstIt += 1;
            secondIt += 1;
        } while (firstIt != firstPath.rend() && secondIt != secondPath.rend());

        return *(firstIt - 1);
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

    std::cout << root->findCommon(6, 5)->value << std::endl;
}