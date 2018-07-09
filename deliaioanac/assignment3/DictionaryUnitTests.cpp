#include "Dictionary.cpp"
#include <gtest/gtest.h>

namespace {
    class DictionaryTest : public ::testing::Test {
        protected:
            static std::unique_ptr<Trie> trie;

            static void SetUpTestCase() {
                std::vector<std::string> elements = {"car", "card", "cart", "cat"};

                trie = std::unique_ptr<Trie>(new Trie());

                for (std::string e : elements) {
                    trie->insert(e);
                }
            }
    };

    std::unique_ptr<Trie> DictionaryTest::trie;
    std::vector<std::string> testWords = {"", "cat", "cart", "ca", "cards", "invalid", "c", "car", "cars"};

    TEST_F(DictionaryTest, EmptyWord) {
        EXPECT_FALSE(trie->isWord(testWords[0]));
    }
    
    TEST_F(DictionaryTest, CompleteWord1) {
        EXPECT_TRUE(trie->isWord(testWords[1]));
    }

    TEST_F(DictionaryTest, CompleteWord2) {
        EXPECT_TRUE(trie->isWord(testWords[2]));
    }

    TEST_F(DictionaryTest, IncompleteWord) {
        EXPECT_FALSE(trie->isWord(testWords[3]));
    }

    TEST_F(DictionaryTest, CompleteWordWithSuffix) {
        EXPECT_FALSE(trie->isWord(testWords[4]));
    }

    TEST_F(DictionaryTest, InvalidWord) {
        EXPECT_FALSE(trie->isWord(testWords[5]));
    }

    TEST_F(DictionaryTest, EmptyPrefix) {
        EXPECT_NE(trie->isPrefix(testWords[0]), nullptr);
        EXPECT_EQ(trie->isPrefix(testWords[0])->value, ' ');
    }

    TEST_F(DictionaryTest, ValidPrefix1) {
        EXPECT_NE(trie->isPrefix(testWords[6]), nullptr);
        EXPECT_EQ(trie->isPrefix(testWords[6])->value, 'c');
    }

    TEST_F(DictionaryTest, ValidPrefix2) {
        EXPECT_NE(trie->isPrefix(testWords[3]), nullptr);
        EXPECT_EQ(trie->isPrefix(testWords[3])->value, 'a');
    }

    TEST_F(DictionaryTest, PrefixThatIsWord) {
        EXPECT_NE(trie->isPrefix(testWords[7]), nullptr);
        EXPECT_EQ(trie->isPrefix(testWords[7])->value, 'r');
    }

    TEST_F(DictionaryTest, InvalidPrefix1) {
        EXPECT_EQ(trie->isPrefix(testWords[5]), nullptr);
    }

    TEST_F(DictionaryTest, InvalidPrefix2) {
        EXPECT_EQ(trie->isPrefix(testWords[8]), nullptr);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
