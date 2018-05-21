#include "CaseInsensitive.cpp"
#include <gtest/gtest.h>

TEST(CaseInsensitiveTest, EmptyStrings) {
    ASSERT_EQ(true, verifyAnagram("", ""));
}

TEST(CaseInsensitiveTest, EmptyInitialString) {
    ASSERT_EQ(false, verifyAnagram("", "hello"));
}

TEST(CaseInsensitiveTest, EmptyAnagramString) {
    ASSERT_EQ(false, verifyAnagram("heLlo", ""));
}

TEST(CaseInsensitiveTest, AnagramStrings1) {
    ASSERT_EQ(true, verifyAnagram("duSTy", "study"));
}

TEST(CaseInsensitiveTest, AnagramStrings2) {
    ASSERT_EQ(true, verifyAnagram("cat", "act"));
}

TEST(CaseInsensitiveTest, AnagramStrings3) {
    ASSERT_EQ(true, verifyAnagram("nigHt", "thInG"));
}

TEST(CaseInsensitiveTest, NonAnagramStrings1) {
    ASSERT_EQ(false, verifyAnagram("night", "hing"));
}

TEST(CaseInsensitiveTest, NonAnagramStrings2) {
    ASSERT_EQ(false, verifyAnagram("cat", "acc"));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
