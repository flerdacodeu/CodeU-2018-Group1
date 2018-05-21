#include "CaseSensitive.cpp"
#include <gtest/gtest.h>

TEST(CaseSensitiveTest, EmptyStrings) {
    ASSERT_EQ(true, verifyAnagram(false, "", ""));
}

TEST(CaseSensitiveTest, EmptyInitialString) {
    ASSERT_EQ(false, verifyAnagram(false, "", "hello"));
}

TEST(CaseSensitiveTest, EmptyAnagramString) {
    ASSERT_EQ(false, verifyAnagram(false, "hello", ""));
}

TEST(CaseSensitiveTest, CaseInsensitiveAnagramStrings1) {
    ASSERT_EQ(true, verifyAnagram(false, "dusty", "study"));
}

TEST(CaseSensitiveTest, CaseInsensitiveAnagramStrings2) {
    ASSERT_EQ(true, verifyAnagram(false, "cat", "act"));
}

TEST(CaseSensitiveTest, CaseInsensitiveAnagramStrings3) {
    ASSERT_EQ(true, verifyAnagram(false, "night", "thing"));
}

TEST(CaseSensitiveTest, CaseInsensitiveNonAnagramStrings1) {
    ASSERT_EQ(false, verifyAnagram(false, "night", "hing"));
}

TEST(CaseSensitiveTest, CaseInsensitiveNonAnagramStrings2) {
    ASSERT_EQ(false, verifyAnagram(false, "cat", "acc"));
}

TEST(CaseSensitiveTest, CaseSensitiveAnagramStrings1) {
    ASSERT_EQ(true, verifyAnagram(true, "Night", "thiNg"));
}

TEST(CaseSensitiveTest, CaseSensitiveAnagramStrings2) {
    ASSERT_EQ(true, verifyAnagram(true, "Cat", "aCt"));
}

TEST(CaseSensitiveTest, CaseSensitiveNonAnagramStrings1) {
    ASSERT_EQ(false, verifyAnagram(true, "DuSty", "Study"));
}

TEST(CaseSensitiveTest, CaseSensitiveNonAnagramStrings2) {
    ASSERT_EQ(false, verifyAnagram(true, "CAT", "acc"));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
