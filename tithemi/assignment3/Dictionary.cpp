#include "Dictionary.hpp"

const Dictionary* Dictionary::findLastNode(const std::string& word) const
{
    const Dictionary* node = this;

    for (const char x : word)
    {
        auto next = node->postfixes_.find(x);

        if (next == node->postfixes_.end())
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
        auto& next = node->postfixes_[x];

        if (next == nullptr)
            next = new Dictionary();

        node = next;
    }

    node->is_terminal_ = true;
}

Dictionary::Dictionary(const std::vector<std::string>& words) : is_terminal_(false)
{
    for (const std::string& word : words)
        add(word);
}

Dictionary::~Dictionary()
{
    for (auto& pair : postfixes_)
        delete pair.second;
}

bool Dictionary::isWord(const std::string& word) const
{
    auto found = findLastNode(word);
    return found != nullptr && found->is_terminal_;
}

bool Dictionary::isPrefix(const std::string& prefix) const
{
    return findLastNode(prefix) != nullptr;
}


