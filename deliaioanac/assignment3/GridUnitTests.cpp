#include "Grid.cpp"
#include <gtest/gtest.h>
#include <algorithm>

namespace {
    class GridTest : public ::testing::Test {
        protected:
            static std::unique_ptr<Grid> grid;

            static void SetUpTestCase() {
                std::vector<std::vector<char> > newGrid = {{'a', 'a', 'r'}, {'t', 'c', 'd'}};
                grid = std::unique_ptr<Grid>(new Grid(newGrid));
            }
    };

    std::unique_ptr<Grid> GridTest::grid;

    TEST_F(GridTest, EmptyDict) {
        std::vector<std::string> elements = {};
        std::unique_ptr<Trie> trie = std::unique_ptr<Trie>(new Trie());

        for (std::string e : elements) {
            trie->insert(e);
        }

        EXPECT_EQ(grid->wordSearch(trie).size(), 0);
    }

    TEST_F(GridTest, EmptyWord) {
        std::vector<std::string> elements = {""};
        std::unique_ptr<Trie> trie = std::unique_ptr<Trie>(new Trie());

        for (std::string e : elements) {
            trie->insert(e);
        }

        EXPECT_EQ(grid->wordSearch(trie).size(), 0);
    }

    TEST_F(GridTest, ValidDict) {
        std::vector<std::string> elements = {"cat", "car", "card", "cart"};
        std::unique_ptr<Trie> trie = std::unique_ptr<Trie>(new Trie());

        for (std::string e : elements) {
            trie->insert(e);
        }

        elements = grid->wordSearch(trie);
        EXPECT_EQ(elements.size(), 3);
        sort(elements.begin(), elements.end());
        EXPECT_EQ(elements[0], "car");
        EXPECT_EQ(elements[1], "card");
        EXPECT_EQ(elements[2], "cat");
    }

    TEST_F(GridTest, DictWithDuplicates) {
        std::vector<std::string> elements = {"cat", "cat", "card", "cart"};
        std::unique_ptr<Trie> trie = std::unique_ptr<Trie>(new Trie());

        for (std::string e : elements) {
            trie->insert(e);
        }

        elements = grid->wordSearch(trie);
        EXPECT_EQ(elements.size(), 2);
        sort(elements.begin(), elements.end());
        EXPECT_EQ(elements[0], "card");
        EXPECT_EQ(elements[1], "cat");
    }

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
