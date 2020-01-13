/**
 * Name: Rickesh Khilnani
 * Email: rikhilna@ucsd.edu
 * 
 * The purpose of the BSTNode file is to create elements in a binary search
 * tree data structure. BSTNode assigns parent and children references to
 * each node, if applicable. BSTNode aids BSTIterator.hpp and BST.hpp for
 * complete implementation of a binary search tree.
 */
#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

/**
 * The BSTNode class instantiated a singular node with a private data 
 * variable, and public left, right, and parent pointers. Includes
 * the successor() method which dictates the functionality of the
 * pre-increment operator in BSTIterator.	
 */
template <typename Data>
class BSTNode {
  private:
    Data data;

  public:
    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;

    /** Initializes a node with given data, with no parent or children */
    BSTNode(const Data& d) : data(d) {
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        //TODO NEED TO TEST
    }

    /** Set the value of data */
    void setData(const Data& d) { data = d; }

    /** Get the value of data */
    Data getData() { return data; }

    /** Returns the successor of this BSTNode. This is the smallest
     *  element that is larger than this BSTNode
     */
    BSTNode<Data>* successor() { 
        return this->parent;
        //TODO NEED TO TEST
    }
};

/**
 * DO NOT CHANGE THIS METHOD
 * Overload operator<< to print a BSTNode's fields to an ostream.
 */
template <typename Data>
ostream& operator<<(ostream& stm, const BSTNode<Data>& n) {
    stm << '[';
    stm << setw(10) << &n;                  // address of the BSTNode
    stm << "; p:" << setw(10) << n.parent;  // address of its parent
    stm << "; l:" << setw(10) << n.left;    // address of its left child
    stm << "; r:" << setw(10) << n.right;   // address of its right child
    stm << "; d:" << n.data;                // its data field
    stm << ']';
    return stm;
}

#endif  // BSTNODE_HPP
