#include "KthToLast.cpp"
#include <gtest/gtest.h>

namespace {
    class KthToLastTest : public ::testing::Test {
        protected:
            ListNode<int> *head;

            virtual void addNext(ListNode<int> *copy, int data) {
                copy->next = (ListNode<int> *) malloc(sizeof(ListNode<int>));
                if (!copy->next) {
                    cerr << "malloc failed" << endl;
                    exit(EXIT_FAILURE);

                }
                copy->next->data = data;
            }

            virtual void SetUp() {
                head = (ListNode<int> *) malloc(sizeof(ListNode<int>));
                if (!head) {
                    cerr << "malloc failed" << endl;
                    exit(EXIT_FAILURE);
                }

                head->data = 0;
                ListNode<int> *copy = head; 
                addNext(copy, 1);
                copy = copy->next;
                addNext(copy, 2);
                copy = copy->next;
                addNext(copy, 3);
                copy = copy->next;
                addNext(copy, 4);
                copy = copy->next;
                copy->next = NULL;
            }

            virtual void TearDown() {
                ListNode<int> *copy;
                while (head != NULL) {
                    copy = head->next;
                    free(head);
                    head = copy;
                }
            }
    };

    TEST_F(KthToLastTest, GetFirst) {
        ASSERT_EQ(4, getKthToLast(head, 0));
    }

    TEST_F(KthToLastTest, GetMiddle) {
        ASSERT_EQ(2, getKthToLast(head, 2));
    }

    TEST_F(KthToLastTest, GetLast) {
        ASSERT_EQ(0, getKthToLast(head, 4));
    }

    TEST_F(KthToLastTest, OutOfBoundsUpper) {
        EXPECT_EXIT(getKthToLast(head, 10), ::testing::ExitedWithCode(EXIT_FAILURE), "");
    }

    TEST_F(KthToLastTest, OutOfBoundsLower) {
        EXPECT_EXIT(getKthToLast(head, -1), ::testing::ExitedWithCode(EXIT_FAILURE), "");
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
