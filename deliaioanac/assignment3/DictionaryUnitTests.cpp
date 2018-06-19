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

    TEST_F(DictionaryTest, EmptyWord) {
        ASSERT_FALSE(trie->isWord(""));
    }
    
    TEST_F(DictionaryTest, CompleteWord1) {
        ASSERT_TRUE(trie->isWord("cat"));
    }

    TEST_F(DictionaryTest, CompleteWord2) {
        ASSERT_TRUE(trie->isWord("cart"));
    }

    TEST_F(DictionaryTest, IncompleteWord) {
        ASSERT_FALSE(trie->isWord("ca"));
    }

    TEST_F(DictionaryTest, CompleteWordWithSuffix) {
        ASSERT_FALSE(trie->isWord("cards"));
    }

    TEST_F(DictionaryTest, InvalidWord) {
        ASSERT_FALSE(trie->isWord("invalid"));
    }

    TEST_F(DictionaryTest, EmptyPrefix) {
        ASSERT_TRUE(trie->isPrefix(""));
    }

    TEST_F(DictionaryTest, ValidPrefix1) {
        ASSERT_TRUE(trie->isPrefix("c"));
    }

    TEST_F(DictionaryTest, ValidPrefix2) {
        ASSERT_TRUE(trie->isPrefix("ca"));
    }

    TEST_F(DictionaryTest, PrefixThatIsWord) {
        ASSERT_TRUE(trie->isPrefix("car"));
    }

    TEST_F(DictionaryTest, InvalidPrefix1) {
        ASSERT_FALSE(trie->isPrefix("invalid"));
    }

    TEST_F(DictionaryTest, InvalidPrefix2) {
        ASSERT_FALSE(trie->isPrefix("cars"));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
