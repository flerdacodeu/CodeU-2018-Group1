#pragma once

#include <unordered_map>

class Dictionary
{
    bool isTerminal = false;

    std::unordered_map<char, Dictionary*> postfixes;


    const Dictionary* findLastNode(const std::string& word) const;

    void add(const std::string& word);

    Dictionary() = default;

public:
    Dictionary(const std::vector<std::string>& words);
    ~Dictionary();

    bool isWord(const std::string& word) const;

    bool isPrefix(const std::string& prefix) const;
};


