#include "LCA.cpp"
#include <gtest/gtest.h>
#include <vector>

namespace {
    class LCATest : public ::testing::Test {
        protected:
            static std::unique_ptr<CustomTree> tree;

            static void SetUpTestCase() {
                /*
                 * Constructing the following tree :
                 * 
                 *                1
                 *               / \
                 *              /   \
                 *             2     3
                 *            /|\   / \
                 *           4 5 6 10  11
                 *          / \  |
                 *         7  8  9
                 */
                std::vector<int> elements = {1, 1, 2, 2, 2, 4, 4, 6, 3, 3};
                tree = std::unique_ptr<CustomTree>(new CustomTree(elements));
                tree->preprocessingLCA();
            }
    };

    std::unique_ptr<CustomTree> LCATest::tree;

    TEST_F(LCATest, ChildrenOfSameNode) {
        ASSERT_EQ(3, tree->getLowestCommonAncestor(10, 11));
    }

    TEST_F(LCATest, FartherUpLCA) {
        ASSERT_EQ(2, tree->getLowestCommonAncestor(8, 9));
    }

    TEST_F(LCATest, DecendantsOfRoot) {
        ASSERT_EQ(1, tree->getLowestCommonAncestor(5, 11));
    }

    TEST_F(LCATest, LCAIsOneOfTheNodes) {
        ASSERT_EQ(2, tree->getLowestCommonAncestor(2, 4));
    }

    TEST_F(LCATest, SameNode) {
        ASSERT_EQ(10, tree->getLowestCommonAncestor(10, 10));
    }

    TEST_F(LCATest, InvalidNode1) {
        ASSERT_EQ(0, tree->getLowestCommonAncestor(0, 10));
    }

    TEST_F(LCATest, InvalidNode2) {
        ASSERT_EQ(0, tree->getLowestCommonAncestor(10, 12));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
