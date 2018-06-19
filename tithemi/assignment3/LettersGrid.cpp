#ifndef LETTERSGRID_CPP_
#define LETTERSGRID_CPP_

#include "LettersGrid.hpp"

static const size_t neighborsCount = 8;
static const size_t neighborsOffsets[neighborsCount][2] =
{
    { -1, -1 },
    { -1, +0 },
    { -1, +1 },
    { +0, -1 },
    { +0, +1 },
    { +1, -1 },
    { +1, +0 },
    { +1, +1 }
};

template <size_t Rows, size_t Columns>
void LettersGrid<Rows, Columns>::findWords(
    size_t i, size_t j,
    const Dictionary& dictionary,
    std::set<std::string>& result,
    std::string& current,
    bool visited[Rows][Columns]
) const
{
    visited[i][j] = true;
    current.push_back(letters[i][j]);

    if (dictionary.isPrefix(current))
    {
        if (dictionary.isWord(current))
            result.insert(current);

        for (size_t neighborID = 0; neighborID < neighborsCount; ++neighborID)
        {
            size_t neighborRow = i + neighborsOffsets[neighborID][0];
            if (neighborRow >= Rows)
                continue;

            size_t neighborCol = j + neighborsOffsets[neighborID][1];
            if (neighborCol >= Columns)
                continue;

            if (visited[neighborRow][neighborCol])
                continue;

            findWords(neighborRow, neighborCol, dictionary, result, current, visited);
        }
    }

    visited[i][j] = false;
    current.pop_back();
}

template <size_t Rows, size_t Columns>
std::set<std::string> LettersGrid<Rows, Columns>::findWords(const Dictionary& dictionary) const
{
    bool visited[Rows][Columns] = { {false} };
    std::set<std::string> result;
    std::string current;

    for (size_t i = 0; i < Rows; ++i)
        for (size_t j = 0; j < Columns; ++j)
            findWords(i, j, dictionary, result, current, visited);

    return result;
}

#endif