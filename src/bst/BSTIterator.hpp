/**
 * Name: Rickesh Khilnani
 * Email: rikhilna@ucsd.edu
 *
 * The purpose of the BSTIterator file is to create iterators that will
 * traverse through a binary search tree. Each iterator will point to
 * an element in the tree. BSTIterator uses methods from BSTNode for 
 * complete implementation of a binary search tree. 
 */
#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include <iterator>
#include <list>
#include "BSTNode.hpp"

using namespace std;

/**
 * The BSTIterator class instantiates an iterator that will point to
 * a BSTNode. Methods for pre and post increment are included so that
 * the iterator may traverse through the BST. Lastly, the two equality
 * operators, == and !=, are overloaded so that testing between two
 * iterators is easier. 
 */
template <typename Data>
class BSTIterator : public iterator<input_iterator_tag, Data> {
  private:
    BSTNode<Data>* curr;

  public:
    /**
     * Constructor that initialize the current BSTNode
     * in this BSTIterator.
     */
    BSTIterator(BSTNode<Data>* curr) : curr(curr) {}

    /** Dereference operator. */
    Data operator*() const { return curr->getData(); }

    /** Pre-increment operator. */
    BSTIterator<Data>& operator++() {
        curr = curr->successor();
        return *this;
    }

    /** Post-increment operator. */
    BSTIterator<Data> operator++(int) {
        BSTIterator before = BSTIterator(curr);
        ++(*this);
        return before;
    }

    /** 
     * Equality test operator. Used to check if two iterators are equivalent
     * to one another. This is the case if two iterators contain the same
     * BST pointer.
     * Parmeters: other - The address to another BSTIterator for equality
     *                    comparison
     */
    bool operator==(BSTIterator<Data> const& other) const {
        return this->curr == other.curr;
    }

    /** 
     * Inequality test operator. Used to check if two iterators are not
     * equivalent to one another. This is the case if two iterators contain
     * different BST pointers.
     * Parameters: other - The address to another BSTIterator for inequality
     *                     comparison
     */
    bool operator!=(BSTIterator<Data> const& other) const { 
        return this->curr != other.curr;
    }
};

#endif  // BSTITERATOR_HPP
