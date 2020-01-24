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

    /**
     * Used as a copy constructor that will create a balanced BST out
     * of the given bst. The given bst is not altered, but only copied.
     * Parameter: bst - the bst to copy
     */
    BST(const BST<Data>& bst) : root(0), isize(0), iheight(-1) {
        if (bst.empty()) {
            BST();
        }
        vector<Data> vec;
        // Puts all of the elements from given bst in inorder in a vector
        iterator iter( bst.begin() );
        while ( iter != end() ) {
            vec.push_back( *iter );
            iter++;
        }
        isize = bst.size();
        root = buildSubtree(vec, 0, bst.size(), 0);
        iheight = checkHeight(root) - 1;
    }

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
     
        if (find(item) != end())
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
                    if (heightToRecord > iheight) {
                        iheight = heightToRecord;
                    }
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
                    if (heightToRecord > iheight) {
                        iheight = heightToRecord;
                    }
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
            return end();

        iterator iter( findNodeHelper(root, item) );
        return iter;
    }

    /** 
     * Deletes a node with the given data. If no data is found, return false
     * Parameter: item - the data to delete in the bst
     */
    bool deleteNode(const Data& item) {
        // If the item is not found, return false
        if ( find(item) == end() )
            return false;

        // Finds the node to delete and creates a pointer to it
        BSTNode<Data>* nodeToDelete = findNodeHelper(root, item);
        // Whether or not the node has a left or right child or a parent node
        bool hasLeft = nodeToDelete->left != 0;
        bool hasRight = nodeToDelete->right != 0;
        bool hasParent = nodeToDelete->parent != 0;
        // If the node to delete is a right child of its parent or a left
        bool ifParentsRight = false;
        bool ifParentsLeft = false;
        // Set the respective bool true if the node has a parent at all
        if (hasParent) {
            ifParentsRight = nodeToDelete->parent->right == nodeToDelete;
            ifParentsLeft = nodeToDelete->parent->left == nodeToDelete;
        }

        // If the node doesn't have children
        if ( !hasLeft && !hasRight ) {
            // Checks if node to delete is root
            if (hasParent) {
                // "Cuts" the node to delete out of the bst
                if ( ifParentsRight )
                    nodeToDelete->parent->right = 0;
                else if ( ifParentsLeft )
                    nodeToDelete->parent->left = 0;
            }
        // If the node has a left child, but not a right
        } else if ( hasLeft && !hasRight ) {
            if (hasParent) {
                if ( ifParentsRight )
                    nodeToDelete->parent->right = nodeToDelete->left;
                else
                    nodeToDelete->parent->left = nodeToDelete->left;
                nodeToDelete->left->parent = nodeToDelete->parent;
            } else
                root = nodeToDelete->left;
            delete nodeToDelete;
        // If the node has a right child, but not a left
        } else if ( !hasLeft && hasRight ) {
            if (hasParent) {
                if ( ifParentsRight )
                    nodeToDelete->parent->right = nodeToDelete->right;
                else
                    nodeToDelete->parent->left = nodeToDelete->right;
                nodeToDelete->right->parent = nodeToDelete->parent;
            } else
                root = nodeToDelete->right;
            delete nodeToDelete;
        // If the node has two children
        } else {
            // Updates current node to the successor's data and calls
            // deleteNode on the successor until the successor is a
            // leaf node
            Data succData = nodeToDelete->successor()->getData();
            deleteNode( succData );
            isize++;
            nodeToDelete->setData( succData );
        }
        iheight = checkHeight(root) - 1;
        isize--;
        return true;         
    }

    /** Returns the number of items currently in the BST. */
    unsigned int size() const { return isize; }

    /** Returns the height of the BST */
    int height() const { 
        if (empty())
            return -1;
        return iheight;
    }

    /** Returns true if the BST is empty, else false */
    bool empty() const { return isize == 0; }

    /** Returns an iterator pointing to the first item in the BST. */
    iterator begin() const {
        if (empty())
            return end();
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
     * Finds a node with the given Data and returns a pointer to it
     * Parameters: root - the root node of the bst to work off of
     *             item - the data to find in the bst
     */
    BSTNode<Data>* findNodeHelper(BSTNode<Data>* root, 
                                  const Data& item) const { 
        BSTNode<Data>* testingNode = root;
        // While testingNode is not null
        while (testingNode != 0 && (item < testingNode->getData() ||
               testingNode->getData() < item)) {
            // If item is less than the current node, go the left subtree
            // else go to the right
            if (item < testingNode->getData())
                testingNode = testingNode->left;
            else
                testingNode = testingNode->right;
        }
        return testingNode;
    }

    /**
     * Runs through the bst and updates height
     * Parameters: root - the pointer to the parent node so that the
     *                    children's height can be checked
     */
    int checkHeight(BSTNode<Data>* root) {
        if (root == 0) return 0;
        int left_height = checkHeight(root->left);
        int right_height = checkHeight(root->right);
        if (left_height > right_height)
            return left_height + 1;
        return right_height + 1;
    }

    /** 
     * Helper function for inorder() 
     * Parameters: curr - The pointer to the node that the inorder traversal
     *                    will be performed on
     *             v - The vector that will store the Data of the nodes
     */
    void inorderHelper(BSTNode<Data>* curr, vector<Data> &v) const {
        if (curr == 0)
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
        while (testingNode->left != 0)
            testingNode = testingNode->left;
        return testingNode;
    }

    /** 
     * Recursively deletes all of the nodes in the BST.
     * Parameters: n - the pointer to the node whos left subtree will
     *                 be deleted, then the node itself, and then the
     *                 right subtree
     */
    void deleteAll(BSTNode<Data>* n) {
        /* Pseudocode:
           if current node is null: return;
           recursively delete left sub-tree
           recursively delete right sub-tree
           delete current node
        */
        if (n == 0)
            return;
        if (n->left != 0)
            deleteAll(n->left);
        if (n->right != 0)
            deleteAll(n->right);
        delete n;
    }

    /**
     * Builds a balanced subtree given a vector, and a start and end position
     * in the vector (the start is inclusive and the end is exclusive)
     * Parameters: data - the vector which contains the elements in inorder
     *                    traversal
     *             start - the starting index in the data vector to build
     *             end - the ending index in the data vector to build
     *             depth - not used
     */
    BSTNode<Data>* buildSubtree(vector<Data>& data, int start, int end,
                                int depth) {
        if (start == end)
            return 0;

        short medianDivider = 2;
        int median = ( start + end ) / medianDivider;
        BSTNode<Data>* medianNode = new BSTNode<Data>( data.at(median) );
  
        BSTNode<Data>* leftChild = buildSubtree(data, start, median, depth);
        int afterMedian = median + 1;
        BSTNode<Data>* rightChild = buildSubtree(data, afterMedian, 
                                                 end, depth);
        medianNode->left = leftChild;
        medianNode->right = rightChild;
        if ( medianNode->left != 0 )
            medianNode->left->parent = medianNode;
        if ( medianNode->right != 0 )
            medianNode->right->parent = medianNode;

        return medianNode;
    }
};

#endif  // BST_HPP
