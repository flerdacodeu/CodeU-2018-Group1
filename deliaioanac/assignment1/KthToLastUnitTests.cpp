#include "KthToLast.cpp"
#include <gtest/gtest.h>

namespace {
    class KthToLastTest : public ::testing::Test {
        protected:
            CustomList<int> list;

            virtual void SetUp() {
                std::vector<int> elements = {4, 3, 2, 1};
                list.addElements(elements);
            }

            virtual void TearDown() {
                list.destroyList(); 
            }
    };

    TEST_F(KthToLastTest, GetFirst) {
        ASSERT_EQ(4, list.getKthToLast(0));
    }

    TEST_F(KthToLastTest, GetMiddle) {
        ASSERT_EQ(2, list.getKthToLast(2));
    }

    TEST_F(KthToLastTest, GetLast) {
        ASSERT_EQ(1, list.getKthToLast(3));
    }

    TEST_F(KthToLastTest, OutOfBoundsUpper) {
        EXPECT_THROW(list.getKthToLast(10), std::out_of_range);
    }

    TEST_F(KthToLastTest, OutOfBoundsLower) {
        EXPECT_THROW(list.getKthToLast(-1), std::out_of_range);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
