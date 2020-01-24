#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BST.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty BST test starts here */

TEST(BSTTests, EMPTY_TREE_HEIGHT_TEST) {
    BST<int> bst;
    ASSERT_EQ(bst.height(), -1);
    ASSERT_EQ(bst.size(), 0);
    ASSERT_TRUE(bst.empty());
}

/* Small BST test starts here */

/**
 * A simple test fixture from which multiple tests
 * can be created. All fixture tests (denoted by the
 * TEST_F macro) can access the protected members of this
 * fixture. Its data is reset after every test.
 *
 * Builds the following BST:
 *         3
 *        / \
 *       1   4
 *      /     \
 *    -33     100
 */
class SmallBSTFixture : public ::testing::Test {
  protected:
    BST<int> bst;

  public:
    SmallBSTFixture() {
        // initialization code here
        vector<int> input{3, 4, 1, 100, -33};
        insertIntoBST(input, bst);
    }
    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

TEST_F(SmallBSTFixture, INORDER_TEST) {
    vector<int> vec1 = bst.inorder();
    vector<int> vec2 = {-33, 1, 3, 4, 100};
    ASSERT_EQ(vec1, vec2);
    ASSERT_FALSE(bst.empty());
}

TEST_F(SmallBSTFixture, SMALL_FIND_TEST) {
    ASSERT_EQ(*bst.find(3), 3); 
}

TEST_F(SmallBSTFixture, SMALL_SIZE_TEST) {
    // assert that the small BST has the correct size
    ASSERT_EQ(bst.size(), 5);
}

TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST) {
    // assert failed duplicate insertion
    ASSERT_FALSE(bst.insert(3));
}

TEST_F(SmallBSTFixture, SMALL_HEIGHT_TEST) {
    ASSERT_EQ(bst.height(), 2);
}

TEST_F(SmallBSTFixture, SMALL_INSERT) {
    ASSERT_TRUE(bst.insert(2));
}

TEST_F(SmallBSTFixture, OMEGA_INSERT) {
    ASSERT_FALSE(bst.insert(-33));
    ASSERT_TRUE(bst.insert(-20));
    ASSERT_TRUE(bst.insert(-30));
    ASSERT_TRUE(bst.insert(-15));
    ASSERT_EQ(*bst.begin(), -33);
    ASSERT_TRUE(bst.insert(-509));
    ASSERT_TRUE(bst.insert(-250));
    ASSERT_TRUE(bst.insert(-240));
    ASSERT_TRUE(bst.insert(-245));
    ASSERT_EQ(*bst.begin(), -509);
    ASSERT_FALSE(bst.insert(-30));
    ASSERT_EQ(bst.height(), 6);
    ostream* out = &cout;
    bst.print(out);
}

TEST(BSTNEW, ALL_YESSUH) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(3));
    ASSERT_TRUE(bst.insert(1));
    ASSERT_TRUE(bst.insert(-33));
    ASSERT_TRUE(bst.insert(4));
    ASSERT_TRUE(bst.insert(100));
    ASSERT_EQ(bst.size(), 5);
    ASSERT_EQ(bst.height(), 2);
    ASSERT_EQ(*bst.find(3), 3);
    ASSERT_EQ(*bst.find(1), 1);
    ASSERT_EQ(*bst.find(-33), -33);
    ASSERT_EQ(*bst.find(4), 4);
    ASSERT_EQ(*bst.find(100), 100);
    
    vector<int> vec1 = bst.inorder();
    vector<int> vec2 = {-33, 1, 3, 4, 100};
    ASSERT_EQ(vec1, vec2);
}

TEST(BSTNEW, DELETE_TESTING_LEAF) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(3));
    ASSERT_TRUE(bst.insert(1));
    ASSERT_TRUE(bst.insert(10));
    ASSERT_TRUE(bst.deleteNode(10));
}

TEST(BSTNEW, DELETE_TESTING_LEFTCHILD) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(3));
    ASSERT_TRUE(bst.insert(1));
    ASSERT_TRUE(bst.insert(10));
    ASSERT_TRUE(bst.insert(7));
    ASSERT_EQ(bst.height(), 2);
    ASSERT_TRUE(bst.deleteNode(10));
    ASSERT_EQ(bst.height(), 1);
}

TEST(BSTNEW, DELETE_TESTING_RIGHTCHILD) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(3));
    ASSERT_TRUE(bst.insert(1));
    ASSERT_TRUE(bst.insert(10));
    ASSERT_TRUE(bst.insert(12));
    ASSERT_EQ(bst.height(), 2);
    ASSERT_TRUE(bst.deleteNode(10));
    ASSERT_EQ(bst.height(), 1);
}

TEST(BSTNEW, DELETE_TESTING_ROOT_3NODES) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(3));
    ASSERT_TRUE(bst.insert(1));
    ASSERT_TRUE(bst.insert(10));
    ASSERT_TRUE(bst.deleteNode(3));
    ASSERT_EQ(bst.height(), 1);
    ASSERT_EQ(*bst.begin(), 1);
}

TEST(BSTNEW, DELETE_TESTING_ROOT_2NODES) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(3));
    ASSERT_TRUE(bst.insert(1));
    ASSERT_EQ(bst.height(), 1);
    ASSERT_TRUE(bst.deleteNode(3));
    ASSERT_EQ(bst.height(), 0);
    ASSERT_EQ(*bst.begin(), 1);
}

TEST(BSTNEW, DELETE_TESTING_LEAF_7NODES) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(10));
    ASSERT_TRUE(bst.insert(7));
    ASSERT_TRUE(bst.insert(15));
    ASSERT_TRUE(bst.insert(1));
    ASSERT_TRUE(bst.insert(9));
    ASSERT_TRUE(bst.insert(12));
    ASSERT_TRUE(bst.insert(20));
    ASSERT_EQ(bst.height(), 2);
    ASSERT_TRUE(bst.deleteNode(1));
    ASSERT_TRUE(bst.deleteNode(20));
    ASSERT_EQ(bst.height(), 2);
    ASSERT_EQ(*bst.begin(), 7);
}

TEST(BSTNEW, BALANCE_TESTING) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(5));
    ASSERT_TRUE(bst.insert(4));
    ASSERT_TRUE(bst.insert(3));
    ASSERT_EQ(bst.height(), 2);
    BST<int> bstBalanced = BST<int>(bst);
    ASSERT_EQ(bstBalanced.height(), 1);
    ASSERT_EQ(*bstBalanced.begin(), 3);
    ASSERT_FALSE(bstBalanced.empty());
    ASSERT_EQ(bstBalanced.size(), 3);
}

TEST(BSTNEW, ADD_THEN_DELETE_NODE) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(2));
    ASSERT_TRUE(bst.deleteNode(2));
    ASSERT_TRUE(bst.empty());
}

TEST(BST_START_TO_FINISH, NOARG_CONSTRUCTOR) {
    BST<int> bst;
    ASSERT_EQ(bst.size(), 0);
    ASSERT_EQ(bst.height(), -1);
}

TEST(BST_START_TO_FINISH, COPY_CONSTRUCTOR_EMPTY) {
    BST<int> bst;
    BST<int> bstCopy(bst);
    ASSERT_EQ(bstCopy.size(), 0);
    ASSERT_EQ(bstCopy.height(), -1);
}

TEST(BST_START_TO_FINISH, COPY_CONSTRUCTOR_ONE_ELEMENT) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(30));
    BST<int> bstCopy(bst);
    ASSERT_FALSE(bstCopy.empty());
    ASSERT_EQ(bstCopy.size(), 1);
    ASSERT_EQ(bstCopy.height(), 0);
    ASSERT_EQ(*bstCopy.begin(), 30);
    vector<int> vec1 = bstCopy.inorder();
    vector<int> vec2 = {30};
    ASSERT_EQ(vec1, vec2);
}

TEST(BST_START_TO_FINISH, COPY_CONSTRUCTOR_FIVE_ELEMENTS_RIGHTSKEWED) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(30));
    ASSERT_TRUE(bst.insert(31));
    ASSERT_TRUE(bst.insert(32));
    ASSERT_TRUE(bst.insert(33));
    ASSERT_TRUE(bst.insert(34));
    BST<int> bstCopy(bst);
    ASSERT_FALSE(bstCopy.empty());
    ASSERT_EQ(bstCopy.size(), 5);
    ASSERT_EQ(bstCopy.height(), 2);
    ASSERT_EQ(*bstCopy.begin(), 30);
    vector<int> vec1 = bstCopy.inorder();
    vector<int> vec2 = {30, 31, 32, 33, 34};
    ASSERT_EQ(vec1, vec2);
}

TEST(BST_START_TO_FINISH, COPY_CONSTRUCTOR_FIVE_ELEMENTS_LEFTSKEWED) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(10));
    ASSERT_TRUE(bst.insert(5));
    ASSERT_TRUE(bst.insert(3));
    ASSERT_TRUE(bst.insert(1));
    ASSERT_TRUE(bst.insert(-10));
    BST<int> bstCopy(bst);
    ASSERT_FALSE(bstCopy.empty());
    ASSERT_EQ(bstCopy.size(), 5);
    ASSERT_EQ(bstCopy.height(), 2);
    ASSERT_EQ(*bstCopy.begin(), -10);
    vector<int> vec1 = bstCopy.inorder();
    vector<int> vec2 = {-10, 1, 3, 5, 10};
    ASSERT_EQ(vec1, vec2);
}

TEST(BST_START_TO_FINISH, INSERT_FIRSTELEMENT) {
    BST<int> bst;
    ASSERT_EQ(bst.size(), 0);
    ASSERT_EQ(bst.height(), -1);
    ASSERT_TRUE(bst.insert(5));
    ASSERT_EQ(*bst.begin(), 5);
    ASSERT_EQ(bst.size(), 1);
    ASSERT_EQ(bst.height(), 0);
    vector<int> vec1 = bst.inorder();
    vector<int> vec2 = {5};
    ASSERT_EQ(vec1, vec2);
}

TEST(BST_START_TO_FINISH, INSERT_DUPLICATE_ITEM) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(4));
    ASSERT_FALSE(bst.insert(4));
    ASSERT_EQ(bst.size(), 1);
    ASSERT_EQ(bst.height(), 0);
    ASSERT_EQ(*bst.begin(), 4);
}

TEST(BST_START_TO_FINISH, INSERT_EXTRA_NODE_LEFT) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(4));
    ASSERT_TRUE(bst.insert(2));
    ASSERT_EQ(bst.size(), 2);
    ASSERT_EQ(bst.height(), 1);
    ASSERT_EQ(*bst.begin(), 2);
}

TEST(BST_START_TO_FINISH, INSERT_EXTRA_NODE_LEFT_LEFT) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(4));
    ASSERT_TRUE(bst.insert(2));
    ASSERT_TRUE(bst.insert(1));
    ASSERT_EQ(bst.size(), 3);
    ASSERT_EQ(bst.height(), 2);
    ASSERT_EQ(*bst.begin(), 1);
}

TEST(BST_START_TO_FINISH, INSERT_EXTRA_NODE_RIGHT) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(4));
    ASSERT_TRUE(bst.insert(6));
    ASSERT_EQ(bst.size(), 2);
    ASSERT_EQ(bst.height(), 1);
    ASSERT_EQ(*bst.begin(), 4);
}

TEST(BST_START_TO_FINISH, INSERT_EXTRA_NODE_RIGHT_RIGHT) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(4));
    ASSERT_TRUE(bst.insert(6));
    ASSERT_TRUE(bst.insert(8));
    ASSERT_EQ(bst.size(), 3);
    ASSERT_EQ(bst.height(), 2);
    ASSERT_EQ(*bst.begin(), 4);
}

TEST(BST_START_TO_FINISH, INSERT_EXTRA_NODE_RIGHT_LEFT_RIGHT_LEFT) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(4));
    ASSERT_TRUE(bst.insert(10));
    ASSERT_TRUE(bst.insert(5));
    ASSERT_TRUE(bst.insert(9));
    ASSERT_TRUE(bst.insert(6));
    ASSERT_EQ(bst.size(), 5);
    ASSERT_EQ(bst.height(), 4);
    ASSERT_EQ(*bst.begin(), 4);
    vector<int> vec1 = bst.inorder();
    vector<int> vec2 = {4, 5, 6, 9, 10};
    ASSERT_EQ(vec1, vec2);
}

TEST(BST_START_TO_FINISH, INSERT_EXTRA_NODE_LEFT_RIGHT_RIGHT_LEFT) {
    BST<int> bst;
    ASSERT_TRUE(bst.insert(6));
    ASSERT_TRUE(bst.insert(-10));
    ASSERT_TRUE(bst.insert(2));
    ASSERT_TRUE(bst.insert(4));
    ASSERT_TRUE(bst.insert(3));
    ASSERT_EQ(bst.size(), 5);
    ASSERT_EQ(bst.height(), 4);
    ASSERT_EQ(*bst.begin(), -10);
    vector<int> vec1 = bst.inorder();
    vector<int> vec2 = {-10, 2, 3, 4, 6};
    ASSERT_EQ(vec1, vec2);
}

TEST(BST_START_TO_FINISH, DELETE_ROOT_NODE_NOT_FOUND) {
    BST<int> bst;
    ASSERT_EQ(bst.size(), 0);
    ASSERT_EQ(bst.height(), -1);
    ASSERT_TRUE(bst.insert(2));
    ASSERT_EQ(bst.size(), 1);
    ASSERT_EQ(bst.height(), 0);
    ASSERT_FALSE(bst.deleteNode(50));
    ASSERT_EQ(bst.size(), 1);
    ASSERT_EQ(bst.height(), 0);
    ASSERT_EQ(*bst.begin(), 2);
}

TEST(BST_START_TO_FINISH, DELETE_ROOT_NODE_NO_CHILDREN) {
    BST<int> bst;
    ASSERT_EQ(bst.size(), 0);
    ASSERT_EQ(bst.height(), -1);
    ASSERT_TRUE(bst.insert(5));
    ASSERT_EQ(bst.size(), 1);
    ASSERT_EQ(bst.height(), 0);
    ASSERT_TRUE(bst.deleteNode(5));
    ASSERT_EQ(bst.size(), 0);
    ASSERT_EQ(bst.height(), -1);
}

TEST(BST_START_TO_FINISH, DELETE_LEAF_NODE_LEFT) {
    BST<int> bst;
    ASSERT_EQ(bst.size(), 0);
    ASSERT_EQ(bst.height(), -1);
    ASSERT_TRUE(bst.insert(5));
    ASSERT_EQ(bst.size(), 1);
    ASSERT_EQ(bst.height(), 0);
    ASSERT_TRUE(bst.insert(3));
    ASSERT_EQ(bst.size(), 2);
    ASSERT_EQ(bst.height(), 1);
    ASSERT_EQ(*bst.begin(), 3);
    ASSERT_TRUE(bst.deleteNode(3));
    ASSERT_EQ(*bst.begin(), 5);
    ASSERT_EQ(bst.size(), 1);
    ASSERT_EQ(bst.height(), 0);
    ASSERT_TRUE(bst.deleteNode(5));
    ASSERT_EQ(bst.size(), 0);
    ASSERT_EQ(bst.height(), -1);
}

TEST(BST_START_TO_FINISH, DELETE_LEAF_NODE_RIGHT) {
    BST<int> bst;
    ASSERT_EQ(bst.size(), 0);
    ASSERT_EQ(bst.height(), -1);
    ASSERT_TRUE(bst.insert(5));
    ASSERT_EQ(bst.size(), 1);
    ASSERT_EQ(bst.height(), 0);
    ASSERT_TRUE(bst.insert(7));
    ASSERT_EQ(bst.size(), 2);
    ASSERT_EQ(bst.height(), 1);
    ASSERT_EQ(*bst.begin(), 5);
    ASSERT_TRUE(bst.deleteNode(7));
    ASSERT_EQ(*bst.begin(), 5);
    ASSERT_EQ(bst.size(), 1);
    ASSERT_EQ(bst.height(), 0);
    ASSERT_TRUE(bst.deleteNode(5));
    ASSERT_EQ(bst.size(), 0);
    ASSERT_EQ(bst.height(), -1);
}

TEST(BST_START_TO_FINISH, DELETE_PARENT_THEN_LEFT_LEAF) {
    BST<int> bst;
    ASSERT_EQ(bst.size(), 0);
    ASSERT_EQ(bst.height(), -1);
    ASSERT_TRUE(bst.insert(5));
    ASSERT_EQ(bst.size(), 1);
    ASSERT_EQ(bst.height(), 0);
    ASSERT_TRUE(bst.insert(3));
    ASSERT_EQ(bst.size(), 2);
    ASSERT_EQ(bst.height(), 1);
    ASSERT_EQ(*bst.begin(), 3);
    ASSERT_TRUE(bst.deleteNode(5));
    ASSERT_EQ(*bst.begin(), 3);
    ASSERT_EQ(bst.size(), 1);
    ASSERT_EQ(bst.height(), 0);
    ASSERT_TRUE(bst.deleteNode(3));
    ASSERT_EQ(bst.size(), 0);
    ASSERT_EQ(bst.height(), -1);
}

TEST(BST_START_TO_FINISH, DELETE_PARENT_THEN_RIGHT_LEAF) {
    BST<int> bst;
    ASSERT_EQ(bst.size(), 0);
    ASSERT_EQ(bst.height(), -1);
    ASSERT_TRUE(bst.insert(5));
    ASSERT_EQ(bst.size(), 1);
    ASSERT_EQ(bst.height(), 0);
    ASSERT_TRUE(bst.insert(7));
    ASSERT_EQ(bst.size(), 2);
    ASSERT_EQ(bst.height(), 1);
    ASSERT_EQ(*bst.begin(), 5);
    ASSERT_TRUE(bst.deleteNode(5));
    ASSERT_EQ(*bst.begin(), 7);
    ASSERT_EQ(bst.size(), 1);
    ASSERT_EQ(bst.height(), 0);
    ASSERT_TRUE(bst.deleteNode(7));
    ASSERT_EQ(bst.size(), 0);
    ASSERT_EQ(bst.height(), -1);
}

TEST(BST_START_TO_FINISH, I_GOT_TIRED_OF_WRITING_TESTS_SO_BIG_BST) {
    BST<int> bst;
    ASSERT_EQ(bst.size(), 0);
    ASSERT_EQ(bst.height(), -1);
    ASSERT_TRUE(bst.insert(40));
    ASSERT_EQ(bst.size(), 1);
    ASSERT_EQ(bst.height(), 0);

    ASSERT_TRUE(bst.insert(20));
    ASSERT_EQ(bst.size(), 2);
    ASSERT_EQ(bst.height(), 1);

    ASSERT_TRUE(bst.insert(60));
    ASSERT_EQ(bst.size(), 3);
    ASSERT_EQ(bst.height(), 1);

    ASSERT_TRUE(bst.insert(10));
    ASSERT_EQ(bst.size(), 4);
    ASSERT_EQ(bst.height(), 2);

    ASSERT_TRUE(bst.insert(80));
    ASSERT_EQ(bst.size(), 5);
    ASSERT_EQ(bst.height(), 2);

    ASSERT_TRUE(bst.insert(30));
    ASSERT_EQ(bst.size(), 6);
    ASSERT_EQ(bst.height(), 2);

    ASSERT_TRUE(bst.insert(50));
    ASSERT_EQ(bst.size(), 7);
    ASSERT_EQ(bst.height(), 2);

    ASSERT_TRUE(bst.insert(35));
    ASSERT_EQ(bst.size(), 8);
    ASSERT_EQ(bst.height(), 3);

    ASSERT_TRUE(bst.insert(45));
    ASSERT_EQ(bst.size(), 9);
    ASSERT_EQ(bst.height(), 3);

    ASSERT_TRUE(bst.deleteNode(40));
    ASSERT_EQ(bst.size(), 8);
    ASSERT_EQ(bst.height(), 3);

    ASSERT_TRUE(bst.deleteNode(60));
    ASSERT_EQ(bst.size(), 7);
    ASSERT_EQ(bst.height(), 3);

    ASSERT_TRUE(bst.deleteNode(20));
    ASSERT_EQ(bst.size(), 6);
    ASSERT_EQ(bst.height(), 2);

    ASSERT_TRUE(bst.deleteNode(30));
    ASSERT_EQ(bst.size(), 5);
    ASSERT_EQ(bst.height(), 2);

    ASSERT_TRUE(bst.deleteNode(35));
    ASSERT_EQ(bst.size(), 4);
    ASSERT_EQ(bst.height(), 2);

    ASSERT_TRUE(bst.deleteNode(50));
    ASSERT_EQ(bst.size(), 3);
    ASSERT_EQ(bst.height(), 1);

    ASSERT_TRUE(bst.deleteNode(45));
    ASSERT_EQ(bst.size(), 2);
    ASSERT_EQ(bst.height(), 1);

    ASSERT_TRUE(bst.deleteNode(80));
    ASSERT_EQ(bst.size(), 1);
    ASSERT_EQ(bst.height(), 0);

    ASSERT_TRUE(bst.deleteNode(10));
    ASSERT_EQ(bst.size(), 0);
    ASSERT_EQ(bst.height(), -1);
}

