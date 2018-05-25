#include "CaseSensitive.cpp"
#include <gtest/gtest.h>

std::string initial, anagram;

TEST(CaseSensitiveTest, EmptyStrings) {
    initial = "";
    anagram = "";
    ASSERT_EQ(true, verifyAnagram(initial, anagram, false));
}

TEST(CaseSensitiveTest, EmptyInitialString) {
    initial = "";
    anagram = "hello";
    ASSERT_EQ(false, verifyAnagram(initial, anagram, false));
}

TEST(CaseSensitiveTest, EmptyAnagramString) {
    initial = "hello";
    anagram = "";
    ASSERT_EQ(false, verifyAnagram(initial, anagram, false));
}

TEST(CaseSensitiveTest, CaseInsensitiveAnagramStrings1) {
    initial = "dusty";
    anagram = "study";
    ASSERT_EQ(true, verifyAnagram(initial, anagram, false));
}

TEST(CaseSensitiveTest, CaseInsensitiveAnagramStrings2) {
    initial = "cat";
    anagram = "act";
    ASSERT_EQ(true, verifyAnagram(initial, anagram, false));
}

TEST(CaseSensitiveTest, CaseInsensitiveAnagramStrings3) {
    initial = "night";
    anagram = "thing";
    ASSERT_EQ(true, verifyAnagram(initial, anagram, false));
}

TEST(CaseSensitiveTest, CaseInsensitiveNonAnagramStrings1) {
    initial = "night";
    anagram = "hing";
    ASSERT_EQ(false, verifyAnagram(initial, anagram, false));
}

TEST(CaseSensitiveTest, CaseInsensitiveNonAnagramStrings2) {
    initial = "cat";
    anagram = "acc";
    ASSERT_EQ(false, verifyAnagram(initial, anagram, false));
}

TEST(CaseSensitiveTest, CaseSensitiveAnagramStrings1) {
    initial = "Night";
    anagram = "thiNg";
    ASSERT_EQ(true, verifyAnagram(initial, anagram, true));
}

TEST(CaseSensitiveTest, CaseSensitiveAnagramStrings2) {
    initial = "Cat";
    anagram = "aCt";
    ASSERT_EQ(true, verifyAnagram(initial, anagram, true));
}

TEST(CaseSensitiveTest, CaseSensitiveNonAnagramStrings1) {
    initial = "DuSty";
    anagram = "Study";
    ASSERT_EQ(false, verifyAnagram(initial, anagram, true));
}

TEST(CaseSensitiveTest, CaseSensitiveNonAnagramStrings2) {
    initial = "CAT";
    anagram = "acc";
    ASSERT_EQ(false, verifyAnagram(initial, anagram, true));
}

TEST(CaseSensitiveTest, CaseSensitiveNonAnagramStrings3) {
    initial = "aa";
    anagram = "a";
    ASSERT_EQ(false, verifyAnagram(initial, anagram, true));
}

TEST(CaseSensitiveTest, CaseSensitiveNonAnagramStrings4) {
    initial = "aa";
    anagram = "a";
    ASSERT_EQ(false, verifyAnagram(initial, anagram, false));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
