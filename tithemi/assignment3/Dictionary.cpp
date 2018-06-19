#include "Dictionary.hpp"

const Dictionary* Dictionary::findLastNode(const std::string& word) const
{
    const Dictionary* node = this;

    for (const char x : word)
    {
        auto next = node->postfixes.find(x);

        if (next == node->postfixes.end())
            return nullptr;

        node = next->second;
    }

    return node;
}

void Dictionary::add(const std::string& word)
{
    Dictionary* node = this;

    for (char x : word)
    {
        auto& next = node->postfixes[x];

        if (next == nullptr)
            next = new Dictionary();

        node = next;
    }

    node->isTerminal = true;
}

Dictionary::Dictionary(const std::vector<std::string>& words)
{
    for (const std::string& word : words)
        add(word);
}

Dictionary::~Dictionary()
{
    for (auto& pair : postfixes)
        delete pair.second;
}

bool Dictionary::isWord(const std::string& word) const
{
    auto found = findLastNode(word);
    return found != nullptr && found->isTerminal;
}

bool Dictionary::isPrefix(const std::string& prefix) const
{
    return findLastNode(prefix) != nullptr;
}


