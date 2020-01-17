#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"

using namespace std;
using namespace testing;

TEST(BST_ITERATOR_TEST, TEST_ITERATOR_INCREMENT) {
    BSTNode<int> node(3);
    BSTIterator<int> iter(&node);

    ASSERT_NE(iter, nullptr);

    iter++;

    ASSERT_EQ(iter, nullptr);
}

TEST(BST_ITERATOR_TEST, TEST_ITERATOR_EQUALITY_SAMENODE) {
    BSTNode<int>* node1 = new BSTNode<int>(3);
    BSTIterator<int> iter1(node1);
    BSTIterator<int> iter2(node1);
    ASSERT_TRUE(iter1 == iter2);
    ASSERT_FALSE(iter1 != iter2);
}

TEST(BST_ITERATOR_TEST, TEST_ITERATOR_EQUALITY_DIFFNODE_DIFFDATA) {
    BSTNode<int>* node1 = new BSTNode<int>(3);
    BSTNode<int>* node2 = new BSTNode<int>(4);
    BSTIterator<int> iter1(node1);
    BSTIterator<int> iter2(node2);
    ASSERT_FALSE(iter1 == iter2);
    ASSERT_TRUE(iter1 != iter2);
}

TEST(BST_ITERATOR_TEST, TEST_ITERATOR_EQUALITY_DIFFNODE_SAMEDATA) {
    BSTNode<int>* node1 = new BSTNode<int>(3);
    BSTNode<int>* node2 = new BSTNode<int>(3);
    BSTIterator<int> iter1(node1);
    BSTIterator<int> iter2(node2);
    ASSERT_FALSE(iter1 == iter2);
    ASSERT_TRUE(iter1 != iter2);
}

TEST(BST_ITERATOR_TEST, TEST_ITERATOR_INEQUALITY_SAMENODE) {
    BSTNode<int>* node1 = new BSTNode<int>(3);
    BSTIterator<int> iter1(node1);
    BSTIterator<int> iter2(node1);
    ASSERT_FALSE(iter1 != iter2);
    ASSERT_TRUE(iter1 == iter2);
}

TEST(BST_ITERATOR_TEST, TEST_ITERATOR_INEQUALITY_DIFFNODE_DIFFDATA) {
    BSTNode<int>* node1 = new BSTNode<int>(3);
    BSTNode<int>* node2 = new BSTNode<int>(4);
    BSTIterator<int> iter1(node1);
    BSTIterator<int> iter2(node2);
    ASSERT_TRUE(iter1 != iter2);
    ASSERT_FALSE(iter1 == iter2);
}

TEST(BST_ITERATOR_TEST, TEST_ITERATOR_INEQUALITY_DIFFNODE_SAMEDATA) {
    BSTNode<int>* node1 = new BSTNode<int>(3);
    BSTNode<int>* node2 = new BSTNode<int>(3);
    BSTIterator<int> iter1(node1);
    BSTIterator<int> iter2(node2);
    ASSERT_TRUE(iter1 != iter2);
    ASSERT_FALSE(iter1 == iter2);
}
