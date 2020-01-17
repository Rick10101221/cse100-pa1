#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BSTNode.hpp"

using namespace std;
using namespace testing;

TEST(BST_NODE_TESTS, TEST_CONSTRUCTOR) {
    BSTNode<int>* node = new BSTNode<int>(3);
    ASSERT_EQ(node->left, nullptr);
    ASSERT_EQ(node->right, nullptr);
    ASSERT_EQ(node->parent, nullptr);
    BSTNode<int>* node1 = new BSTNode<int>(3);
    ASSERT_EQ(node1->left, nullptr);
    ASSERT_EQ(node1->right, nullptr);
    ASSERT_EQ(node1->parent, nullptr);
}

TEST(BST_NODE_TESTS, TEST_SUCCESSOR_DEFAULT) {
    BSTNode<int> node(3);
    ASSERT_EQ(node.successor(), nullptr);
}

TEST(BST_NODE_TESTS, TEST_SUCCESSOR_2NODES_LEFT) {
    BSTNode<int>* node1 = new BSTNode<int>(3);
    BSTNode<int>* node2 = new BSTNode<int>(2);
    node1->left = node2;
    node2->parent = node1;
    ASSERT_EQ(node2->successor(), node1);
    ASSERT_EQ(node1->successor(), nullptr);
}

TEST(BST_NODE_TESTS, TEST_SUCCESSOR_2NODES_RIGHT) {
    BSTNode<int>* node1 = new BSTNode<int>(3);
    BSTNode<int>* node2 = new BSTNode<int>(4);
    node1->right = node2;
    node2->parent = node1;
    ASSERT_EQ(node2->successor(), nullptr);
    ASSERT_EQ(node1->successor(), node2);
}

TEST(BST_NODE_TESTS, TEST_SUCCESSOR_3NODES) {
    BSTNode<int>* node1 = new BSTNode<int>(10);
    BSTNode<int>* node2 = new BSTNode<int>(1);
    BSTNode<int>* node3 = new BSTNode<int>(2);
    node1->left = node2;
    node2->right = node3;
    node2->parent = node1;
    node3->parent = node2;
    ASSERT_EQ(node3->successor(), node1);
    ASSERT_EQ(node2->successor(), node3);
    ASSERT_EQ(node1->successor(), nullptr);
}

TEST(BST_NODE_TESTS, TEST_SUCCESSOR_3NODES_LEFTSKEWED) {
    BSTNode<int>* node1 = new BSTNode<int>(3);
    BSTNode<int>* node2 = new BSTNode<int>(2);
    BSTNode<int>* node3 = new BSTNode<int>(1);
    node1->left = node2;
    node2->left = node3;
    node2->parent = node1;
    node3->parent = node2;
    ASSERT_EQ(node2->successor(), node1);
    ASSERT_EQ(node1->successor(), nullptr);
    ASSERT_EQ(node3->successor(), node2);
}

TEST(BST_NODE_TESTS, TEST_SUCCESSOR_3NODES_RIGHTSKEWED) {
    BSTNode<int>* node1 = new BSTNode<int>(1);
    BSTNode<int>* node2 = new BSTNode<int>(2);
    BSTNode<int>* node3 = new BSTNode<int>(3);
    node1->right = node2;
    node2->right = node3;
    node2->parent = node1;
    node3->parent = node2;
    ASSERT_EQ(node2->successor(), node3);
    ASSERT_EQ(node1->successor(), node2);
    ASSERT_EQ(node3->successor(), nullptr);
}

TEST(BST_NODE_TESTS, TEST_SUCCESSOR_5NODES_RIGHTSKEWED) {
    BSTNode<int>* node1 = new BSTNode<int>(10);
    BSTNode<int>* node2 = new BSTNode<int>(1);
    BSTNode<int>* node3 = new BSTNode<int>(2);
    BSTNode<int>* node4 = new BSTNode<int>(3);
    BSTNode<int>* node5 = new BSTNode<int>(4);
    node1->left = node2;
    node2->right = node3;
    node3->right = node4;
    node4->right = node5;
    node2->parent = node1;
    node3->parent = node2;
    node4->parent = node3;
    node5->parent = node4;
    ASSERT_EQ(node5->successor(), node1);
    ASSERT_EQ(node4->successor(), node5);
    ASSERT_EQ(node3->successor(), node4);
    ASSERT_EQ(node2->successor(), node3);
    ASSERT_EQ(node1->successor(), nullptr);
}

TEST(BST_NODE_TESTS, TEST_SUCCESSOR_5NODES_LEFTSKEWED) {
    BSTNode<int>* node1 = new BSTNode<int>(5);
    BSTNode<int>* node2 = new BSTNode<int>(10);
    BSTNode<int>* node3 = new BSTNode<int>(9);
    BSTNode<int>* node4 = new BSTNode<int>(8);
    BSTNode<int>* node5 = new BSTNode<int>(7);
    node1->right = node2;
    node2->left = node3;
    node3->left = node4;
    node4->left = node5;
    node2->parent = node1;
    node3->parent = node2;
    node4->parent = node3;
    node5->parent = node4;
    ASSERT_EQ(node5->successor(), node4);
    ASSERT_EQ(node4->successor(), node3);
    ASSERT_EQ(node3->successor(), node2);
    ASSERT_EQ(node2->successor(), nullptr);
    ASSERT_EQ(node1->successor(), node5);
}

TEST(BST_NODE_TESTS, TEST_SUCCESSOR_6NODES_ZIGZAG) {
    BSTNode<int>* node1 = new BSTNode<int>(5);
    BSTNode<int>* node2 = new BSTNode<int>(10);
    BSTNode<int>* node3 = new BSTNode<int>(6);
    BSTNode<int>* node4 = new BSTNode<int>(9);
    BSTNode<int>* node5 = new BSTNode<int>(7);
    BSTNode<int>* node6 = new BSTNode<int>(8);
    node1->right = node2;
    node2->left = node3;
    node3->right = node4;
    node4->left = node5;
    node5->right = node6;
    node2->parent = node1;
    node3->parent = node2;
    node4->parent = node3;
    node5->parent = node4;
    node6->parent = node5;
    ASSERT_EQ(node6->successor(), node4);
    ASSERT_EQ(node5->successor(), node6);
    ASSERT_EQ(node4->successor(), node2);
    ASSERT_EQ(node3->successor(), node5);
    ASSERT_EQ(node2->successor(), nullptr);
    ASSERT_EQ(node1->successor(), node3);
}

TEST(BST_NODE_TESTS, TEST_SUCCESSOR_6NODES_ZIGZAG2) {
    BSTNode<int>* node1 = new BSTNode<int>(5);
    BSTNode<int>* node2 = new BSTNode<int>(10);
    BSTNode<int>* node3 = new BSTNode<int>(6);
    BSTNode<int>* node4 = new BSTNode<int>(7);
    BSTNode<int>* node5 = new BSTNode<int>(8);
    BSTNode<int>* node6 = new BSTNode<int>(9);
    node1->right = node2;
    node2->left = node3;
    node3->right = node4;
    node4->right = node5;
    node5->right = node6;
    node2->parent = node1;
    node3->parent = node2;
    node4->parent = node3;
    node5->parent = node4;
    node6->parent = node5;
    ASSERT_EQ(node5->successor(), node6);
    ASSERT_EQ(node6->successor(), node2);
    ASSERT_EQ(node4->successor(), node5);
    ASSERT_EQ(node3->successor(), node4);
    ASSERT_EQ(node2->successor(), nullptr);
    ASSERT_EQ(node1->successor(), node3);
}

TEST(BST_NODE_TESTS, TEST_SUCCESSOR_FULLTREE) {
    BSTNode<int>* node1 = new BSTNode<int>(1);
    BSTNode<int>* node2 = new BSTNode<int>(2);
    BSTNode<int>* node3 = new BSTNode<int>(3);
    BSTNode<int>* node4 = new BSTNode<int>(4);
    BSTNode<int>* node5 = new BSTNode<int>(5);
    BSTNode<int>* node6 = new BSTNode<int>(6);
    BSTNode<int>* node7 = new BSTNode<int>(7);
    BSTNode<int>* node8 = new BSTNode<int>(8);
    BSTNode<int>* node9 = new BSTNode<int>(9);
    BSTNode<int>* node10 = new BSTNode<int>(10);
    BSTNode<int>* node11 = new BSTNode<int>(11);
    BSTNode<int>* node12 = new BSTNode<int>(12);
    BSTNode<int>* node13 = new BSTNode<int>(13);
    BSTNode<int>* node14 = new BSTNode<int>(14);
    BSTNode<int>* node15 = new BSTNode<int>(15);
    node8->left = node4;
    node8->right = node12;
    node4->left = node2;
    node4->right = node6;
    node2->left = node1;
    node2->right = node3;
    node6->left = node5;
    node6->right = node7;
    node12->left = node10;
    node12->right = node14;
    node10->left = node9;
    node10->right = node11;
    node14->left = node13;
    node14->right = node15;
    node1->parent = node2;
    node3->parent = node2;
    node5->parent = node6;
    node7->parent = node6;
    node9->parent = node10;
    node11->parent = node10;
    node13->parent = node14;
    node15->parent = node14;
    node2->parent = node4;
    node6->parent = node4;
    node10->parent = node12;
    node14->parent = node12;
    node4->parent = node8;
    node12->parent = node8;
    ASSERT_EQ(node1->successor(), node2);
    ASSERT_EQ(node2->successor(), node3);
    ASSERT_EQ(node3->successor(), node4);
    ASSERT_EQ(node4->successor(), node5);
    ASSERT_EQ(node5->successor(), node6);
    ASSERT_EQ(node6->successor(), node7);
    ASSERT_EQ(node7->successor(), node8);
    ASSERT_EQ(node8->successor(), node9);
    ASSERT_EQ(node9->successor(), node10);
    ASSERT_EQ(node10->successor(), node11);
    ASSERT_EQ(node11->successor(), node12);
    ASSERT_EQ(node12->successor(), node13);
    ASSERT_EQ(node13->successor(), node14); 
    ASSERT_EQ(node14->successor(), node15);
    ASSERT_EQ(node15->successor(), nullptr);
}
