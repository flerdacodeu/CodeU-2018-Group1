#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <stdio.h>
#include <utility>
#include <stdlib.h>
#include <memory>

namespace {
    const int ALPHA_LEN = 26;
}

struct TrieNode {
    bool isEndOfWord;
    char value = ' ';
    std::vector<std::unique_ptr<TrieNode> > children;
    TrieNode(char c) {
        value = c;
        isEndOfWord = false;
        for (int i = 0; i < ALPHA_LEN; i ++) {
            children.push_back(nullptr);
        }
    }
};

class Trie {
    private:
        std::unique_ptr<TrieNode> root_;

        static void insertHelper(const std::unique_ptr<TrieNode> &root, const std::string &word, int i) {
            // Mark the end of the word, so it can be distinguished from a prefix.
            if (i == word.length()) {
                root->isEndOfWord = true;
                return;
            }       

            // If the child (representing the current letter) does not exist already, create it.
            if (!root->children[word[i] - 'a'])
                root->children[word[i] - 'a'] = std::unique_ptr<TrieNode>(new TrieNode(word[i]));

            // Advance to the next letter of the word.
            insertHelper(root->children[word[i] - 'a'], word, i + 1);
        }

        static bool isWordHelper(const std::unique_ptr<TrieNode> &root, const std::string &word, int i) {
            // If all the letters were used, check if this completes a word.
            if (i == word.length())
                return root->isEndOfWord;

            // If the next letter of the word is in the trie, that means
            // the function can advance.
            if (root->children[word[i] - 'a'])
                return isWordHelper(root->children[word[i] - 'a'], word, i + 1);

            // If the next letter does not exist and it is not the end of a word,
            // the word does not exist.
            return false;
        }

        static const TrieNode* const isPrefixHelper(const std::unique_ptr<TrieNode> &root,
                                                                const std::string &prefix, int i) {
            // If all the letters were parsed in the trie, the prefix exists.
            if (i == prefix.length())
                return root.get();
            // If the letter does not exist in the trie, the prefix can't exist.
            else if (!root->children[prefix[i] - 'a'])
                return nullptr;
            else return isPrefixHelper(root->children[prefix[i] - 'a'], prefix, i + 1);
        }

    public:
        Trie() {
            root_ = std::unique_ptr<TrieNode>(new TrieNode(' '));
        }

        // Inserts a word into the trddie.
        void insert(const std::string &word) {
            insertHelper(root_, word, 0);
        }

        // Returns if the word is in the trie.
        bool isWord(const std::string &word) {
            return isWordHelper(root_, word, 0);
        }

        // Returns nullptr if the string is not a valid prefix,
        // otherwise returns the Trie pointer to the last
        // character of the prefix.
        const TrieNode* const isPrefix(const std::string &prefix) {
                return isPrefixHelper(root_, prefix, 0);
        }    
};
