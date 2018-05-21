#include "Sentences.cpp"
#include <gtest/gtest.h>

TEST(SentencesTest, EmptyStrings) {
    ASSERT_EQ(true, verifyAnagram("", ""));
}

TEST(SentencesTest, EmptyInitialSentence) {
    ASSERT_EQ(false, verifyAnagram("", "I am not empty!"));
}

TEST(SentencesTest, EmptyAnagramSentence) {
    ASSERT_EQ(false, verifyAnagram("I am not empty!", ""));
}

TEST(SentencesTest, AnagramSentences1) {
    ASSERT_EQ(true, verifyAnagram("cats study things?", "dusty nights acts."));
}

TEST(SentencesTest, AnagramSentences2) {
    ASSERT_EQ(true, verifyAnagram("bats brag", "tabs !!grab"));
}

TEST(SentencesTest, AnagramSentences3) {
    ASSERT_EQ(true, verifyAnagram("Painters rescue arts...", "Pantries secure rats..."));
}

TEST(SentencesTest, NonAnagramSentences) {
    ASSERT_EQ(false, verifyAnagram("I am independent", "You wish"));
}

TEST(SentencesTest, NonAnagramCase) {
    ASSERT_EQ(false, verifyAnagram("bats brag.", "Tabs grab"));
}

TEST(SentencesTest, NotEnoughPairs) {
    ASSERT_EQ(false, verifyAnagram("Study, Study ladies!", "ideals, duSty ideals"));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
