#pragma once

#include <unordered_map>

class Dictionary
{
    bool is_terminal_;

    std::unordered_map<char, Dictionary*> postfixes_;


    const Dictionary* findLastNode(const std::string& word) const;

    void add(const std::string& word);

    Dictionary() : is_terminal_(false) {}

public:
    Dictionary(const std::vector<std::string>& words);
    ~Dictionary();

    bool isWord(const std::string& word) const;

    bool isPrefix(const std::string& prefix) const;
};


