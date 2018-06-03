#include "printAncestors.cpp"
#include <gtest/gtest.h>
#include <vector>

namespace {
    class PrintAncestorsTest : public ::testing::Test {
        protected:
            BinaryTree tree;

            virtual void SetUp() {
                /*
                 * Constructing the following tree :
                 * 
                 *                1
                 *               / \
                 *              /   \
                 *             2     3
                 *            / \   / \
                 *           4   5 6   7
                 *          / \  /
                 *         8  9 10
                 */
                std::vector<int> elements = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
                tree.createTree(elements);
            }

            virtual void TearDown() {
                tree.destroyTree(); 
            }
    };

    TEST_F(PrintAncestorsTest, Root) {
        testing::internal::CaptureStdout();
        tree.printAncestors(1);
        ASSERT_EQ("\n", testing::internal::GetCapturedStdout());
    }

    TEST_F(PrintAncestorsTest, SecondLevelNode) {
        testing::internal::CaptureStdout();
        tree.printAncestors(2);
        ASSERT_EQ("1\n", testing::internal::GetCapturedStdout());
    }

    TEST_F(PrintAncestorsTest, ThirdLevelNode) {
        testing::internal::CaptureStdout();
        tree.printAncestors(6);
        ASSERT_EQ("3 1\n", testing::internal::GetCapturedStdout());
    }

    TEST_F(PrintAncestorsTest, Leaf) {
        testing::internal::CaptureStdout();
        tree.printAncestors(10);
        ASSERT_EQ("5 2 1\n", testing::internal::GetCapturedStdout());
    }

    TEST_F(PrintAncestorsTest, InvalidNode) {
        testing::internal::CaptureStdout();
        tree.printAncestors(11);
        ASSERT_EQ("Please enter a valid node!\n", testing::internal::GetCapturedStdout());
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
