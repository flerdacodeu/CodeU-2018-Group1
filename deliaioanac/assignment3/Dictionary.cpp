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
    std::vector<std::unique_ptr<TrieNode> > children;
    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < ALPHA_LEN; i ++) {
            children.push_back(nullptr);
        }
    }
};

class Trie {
    private:
        std::unique_ptr<TrieNode> root;

        void insertHelper(std::unique_ptr<TrieNode> &root, std::string word, int i) {
            // Mark the end of the word, so it can be distinguished from a prefix.
            if (i == word.length()) {
                root->isEndOfWord = true;
                return;
            }       

            // If the child (representing the current letter) does not exist already, create it.
            if (!root->children[word[i] - 'a'])
                root->children[word[i] - 'a'] = std::unique_ptr<TrieNode>(new TrieNode());

            // Advance to the next letter of the word.
            insertHelper(root->children[word[i] - 'a'], word, i + 1);
        }

        bool isWordHelper(std::unique_ptr<TrieNode> &root, std::string word, int i) {
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

        bool isPrefixHelper(std::unique_ptr<TrieNode> &root, std::string prefix, int i) {
            // If all the letters were parsed in the trie, the prefix exists.
            if (i == prefix.length())
                return true;
            // If the letter does not exist in the trie, the prefix can't exist.
            else if (!root->children[prefix[i] - 'a'])
                return false;
            else return isPrefixHelper(root->children[prefix[i] - 'a'], prefix, i + 1);
        }

    public:
        Trie() {
            root = std::unique_ptr<TrieNode>(new TrieNode());
        }

        // Inserts a word into the trddie.
        void insert(std::string word) {
            insertHelper(root, word, 0);
        }

        // Returns if the word is in the trie.
        bool isWord(std::string word) {
            return isWordHelper(root, word, 0);
        }

        // Returns if there is any word in the trie
        // that starts with the given prefix.
        bool isPrefix(std::string prefix) {
                return isPrefixHelper(root, prefix, 0);
        }    
};
