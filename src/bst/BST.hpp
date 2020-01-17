/**
 * Name: Rickesh Khilnani
 * Email: rikhilna@ucsd.edu
 *
 * The purpose of the BST file is for the actual construction and
 * modification of BSTs data structures. Utilizes BSTIterator
 * and BSTNode for complete functionality. BSTs will (usually)
 * have a root node accompanied by left and right subtrees of
 * child nodes. A BST is considered as such iff it maintains the
 * property that, for each node with key k, every key in the left
 * subtree must be < than k and every key in the right subtree
 * must be > than k.
 */
#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include <queue>
#include <vector>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

/**
 * The BST class instantiates a binary search tree where the root node
 * is a nullptr, the size of the tree is 0, and the height is -1. Common
 * functions include insert (which will insert a node into the BST while
 * maintaining its tree property), find (which will locate a node in the
 * tree), inorder (lists the nodes in an inorder traversal), and begin
 * (which will return the smallest element in the BST). 
 */
template <typename Data>
class BST {
  protected:
    // pointer to the root of this BST, or 0 if the BST is empty
    BSTNode<Data>* root;

    // number of Data items stored in this BST.
    unsigned int isize;

    // height of this BST.
    int iheight;

  public:
    /** Define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /**
     * Default constructor.
     * Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(-1) {}

    /** */
    BST(const BST<Data>& bst) : root(0), isize(0), iheight(-1) {}

    /** Default destructor. Delete every node in this BST. */
    ~BST() { 
        deleteAll(root);
    }

    /** 
     * Inserts a copy of a Data item into the BST. Accounts for duplicate
     * insertion and returns true if inserted successfully, false if an item
     * equal to the given one is already in the BST.
     * Parameter: item - the Data item to be added to the tree
     */
    bool insert(const Data& item) {
        if (size() == 0) {
            root = new BSTNode<Data>(item);
            isize++;
            iheight++;
            return true;
        }
      
        if (find(item) != nullptr)
            return false;
          
        int heightToRecord = 0;
        // New node to be inserted into the BST
        BSTNode<Data>* newNode = new BSTNode<Data>(item);
        // The node to test newNode with
        BSTNode<Data>* testingNode = root;
        // While the item does not equal an element in the BST and is not null
        while (testingNode != 0 && (item < testingNode->getData() ||
               testingNode->getData() < item)) {
            // If the item is less than the current node, go the left subtree
            // else, go the right subtree
            if (item < testingNode->getData()) {
                if (testingNode->left == 0) {
                    newNode->parent = testingNode;
                    testingNode->left = newNode;
                    isize++;
                    heightToRecord++;
                    if (heightToRecord > iheight)
                        iheight = heightToRecord;
                    return true;
                }
                testingNode = testingNode->left;
                heightToRecord++;
            } else {
                if (testingNode->right == 0) {
                    newNode->parent = testingNode;
                    testingNode->right = newNode;
                    isize++;
                    heightToRecord++;
                    if (heightToRecord > iheight)
                        iheight = heightToRecord;
                    return true;
                }
                testingNode = testingNode->right;
                heightToRecord++;
            }
        }
        return false;
    }

    /** 
     * Returns an iterator pointing to the given Data item in the BST. 
     * If none is found, return an iterator containing the nullptr.
     * Parameter: item - the Data item to be searched for in the tree
     */
    iterator find(const Data& item) const {
        if (empty())
          return NULL;

        BSTNode<Data>* testingNode = root;
        // While testingNode is not null
        while (testingNode != nullptr && (item < testingNode->getData() ||
               testingNode->getData() < item)) {
            // If item is less than the current node, go the left subtree
            // else go to the right
            if (item < testingNode->getData())
                testingNode = testingNode->left;
            else
                testingNode = testingNode->right;
        }

        iterator iter(testingNode);
        return iter;
    }

    /** */
    bool deleteNode(const Data& item) { return false; }

    /** Returns the number of items currently in the BST. */
    unsigned int size() const { return isize; }

    /** Returns the height of the BST */
    int height() const { return iheight; }

    /** Returns true if the BST is empty, else false */
    bool empty() const { return isize == 0; }

    /** Returns an iterator pointing to the first item in the BST. */
    iterator begin() const {
        iterator iter(first(root));
        return iter;
    }

    /** Return an iterator pointing past the last item in the BST. */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** 
     * Performs an inorder traversal of this BST to collect the data of
     * each node in ascending order to a vector
     */
    vector<Data> inorder() const {
        vector<Data> v;
        BSTNode<Data>* curr = root;
        inorderHelper(curr, v);
        return v;
    }

    /**
     * DO NOT CHANGE THIS METHOD
     * Prints a tree, including its structure to an
     * output stream to help with grading and debugging.
     */
    void print(ostream* out) {
        if (empty()) {
            *out << "(Empty tree)" << endl;
            return;
        }

        // Using a queue to traverse a tree is otherwise
        // known as a breadth first traversal of the tree.
        // It's useful here to show which nodes are on which
        // level.
        queue<BSTNode<Data>*> toVisit;
        toVisit.push(root);
        int nodesPerLevel = 1;
        int totalSpacing = 1 << iheight;

        for (int i = 0; i <= iheight; i++) {
            for (int j = 0; j < nodesPerLevel; j++) {
                BSTNode<Data>* curr = toVisit.front();
                toVisit.pop();
                if (curr == nullptr) {
                    *out << "X";
                    // If we have an entire missing subtree, we
                    // would like to print X's in place of all
                    // nodes because it avoids ambiguity
                    toVisit.push(nullptr);
                    toVisit.push(nullptr);
                } else {
                    *out << curr->getData();
                    toVisit.push(curr->left);
                    toVisit.push(curr->right);
                }
                for (int k = 0; k < totalSpacing / nodesPerLevel; k++) {
                    *out << "\t";
                }
            }
            *out << endl;
            nodesPerLevel *= 2;
        }
    }

  private:
    /** 
     * Helper function for inorder() 
     * Parameters: curr - The pointer to the node that the inorder traversal
                          will be performed on
                   v - The vector that will store the Data of the nodes
     */
    void inorderHelper(BSTNode<Data>* curr, vector<Data> &v) const {
        if (curr == nullptr)
            return;
        else {
            inorderHelper(curr->left, v);
            v.push_back(curr->getData());
            inorderHelper(curr->right, v);
        }
    }

    /** 
     * Helper function for begin() 
     * Parameters: root - The pointer to the root node of a BST
     */
    BSTNode<Data>* first(BSTNode<Data>* root) const{
        BSTNode<Data>* testingNode = root;
        while (testingNode->left != nullptr)
            testingNode = testingNode->left;
        return testingNode;
    }

    /** Recursively deletes all of the nodes in the BST. */
    void deleteAll(BSTNode<Data>* n) {
        /* Pseudocode:
           if current node is null: return;
           recursively delete left sub-tree
           recursively delete right sub-tree
           delete current node
        */
        if (n == NULL)
            return;
        if (n->left != NULL)
            deleteAll(n->left);
        if (n->right != NULL)
            deleteAll(n->right);
        delete n;
    }

    /** */
    BSTNode<Data>* buildSubtree(vector<Data>& data, int start, int end,
                                int depth) {
        return 0;
    }

    // Add more helper functions below
};

#endif  // BST_HPP
