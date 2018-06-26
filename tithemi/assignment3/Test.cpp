#include "gtest/gtest.h"
#include "Dictionary.hpp"
#include "LettersGrid.hpp"

static const std::vector<std::string> words =
{
    "CAR", "CARD", "CART", "CAT"
};

static const std::vector<std::string> prefixes =
{
    "C", "CA", "CAR", "CARD", "CART", "CAT"
};

static const int rows = 2;
static const int columns = 3;

static const std::array<std::array<char, columns>, rows> letters = 
{ {
    { 'A', 'A', 'R' },
    { 'T', 'C', 'D' }
} };

TEST(DictionaryIsWorking, ContainsWords)
{
    Dictionary dictionary(words);

    for (const std::string& word : words)
        EXPECT_TRUE(dictionary.isWord(word));

    EXPECT_FALSE(dictionary.isWord(""));
    EXPECT_FALSE(dictionary.isWord("C"));
    EXPECT_FALSE(dictionary.isWord("CA"));
    EXPECT_FALSE(dictionary.isWord(std::string("CAR") + '\0'));
}

TEST(DictionaryIsWorking, ContainsPrefixes)
{
    Dictionary dictionary(words);

    EXPECT_TRUE(dictionary.isPrefix(""));

    for (const std::string& prefix : prefixes)
        EXPECT_TRUE(dictionary.isPrefix(prefix));

    EXPECT_FALSE(dictionary.isPrefix("CAD"));
    EXPECT_FALSE(dictionary.isPrefix("CAA"));
    EXPECT_FALSE(dictionary.isPrefix("A"));
}

TEST(LettersGridIsWorking, ValidWordsAreFound)
{
    std::set<std::string> expected = { "CAR", "CARD", "CAT" };

    LettersGrid<2, 3> grid(letters);
    auto actual = grid.findWords(words);

    EXPECT_EQ(expected, actual);
}

TEST(LettersGridIsWorking, InvalidWordsAreNotFound)
{
    std::set<std::string> expected = { };

    LettersGrid<5, 1> grid({});
    auto actual = grid.findWords(words);

    EXPECT_EQ(expected, actual);
}

TEST(LettersGridIsWorking, EmptyDictionary)
{
    std::set<std::string> expected = {};

    LettersGrid<2, 3> grid(letters);
    auto actual = grid.findWords({ std::vector<std::string>() });

    EXPECT_EQ(expected, actual);
}
