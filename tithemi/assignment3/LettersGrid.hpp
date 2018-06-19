#ifndef LETTERSGRID_HPP_
#define LETTERSGRID_HPP_

#include <array>
#include <set>
#include "Dictionary.hpp"

template <size_t Rows, size_t Columns>
class LettersGrid
{
    const std::array<std::array<char, Columns>, Rows> letters;

    void findWords(
        size_t i, size_t j, 
        const Dictionary& dictionary, 
        std::set<std::string>& result,
        std::string& current,
        bool visited[Rows][Columns]
    ) const;

public:
    LettersGrid(const std::array<std::array<char, Columns>, Rows> letters) : letters(letters) {}

    std::set<std::string> findWords(const Dictionary& dictionary) const;
};

#include "LettersGrid.cpp"

#endif