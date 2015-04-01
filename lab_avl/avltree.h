/**
 * @file avltree.h
 * Declaraction of the AVLTree class. You will probably need to modify this
 *  file to add helper functions.
 * @author Daniel Hoodin in Spring 2008.
 * Modified by Kyle Johnson in Fall 2010.
 * Modified by Sean Massung in Summer 2012:
 *  - added templates
 *  - CRTP tree printing
 *  - doxygen
 */

#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/**
 * The AVLTree class represents a templated linked-memory tree data structure.
 */
template <class K, class V>
class AVLTree
{
	private:

		/**
		 * Represents a tree node; that is, an element in a AVLTree.
		 * It has a data element and pointers to its left and right children.
		 */
		struct Node
		{
			K key;
			V value;
			Node* left;
			Node* right;
			int height;

			/**
			 * Node element constructor; sets children to point to NULL.
             * @param newKey The object to use as a key
			 * @param newValue The templated data element that the constructed
			 *  node will hold.
			 */
			Node(const K & newKey, const V & newValue)
				: key(newKey), value(newValue), left(NULL), right(NULL), height(0) { /* nothing */ }
		};

	public:

		/**
		 * Constructor to create an empty tree.
		 */
		AVLTree();

		/**
		 * Copy constructor.
		 */
		AVLTree(const AVLTree & other);

		/**
		 * Destructor; frees all nodes associated by this tree.
		 */
		~AVLTree();

		/**
		 * Assignment operator.
		 * @param rhs The tree to make a copy of
		 * @return A reference to the current tree
		 */
		const AVLTree & operator=(const AVLTree & rhs);

		/**
		 * Frees all nodes associated with this tree and sets it to be empty.
		 */
		void clear();

		/**
		 * Inserts into the AVLTree.
         * @param key The key to insert
         * @param value The value for the key to insert
		 */
		void insert(const K & key, const V & value);

        /**
         * Finds an element in the AVL tree.
         * @param key The element to search for
         * @return the value stored for that key
         */
		V find(const K & key) const;

        /**
         * Prints the AVLTree to a stream (default stdout).
         * @param out The stream to print to
         */
        void print(ostream & out = cout) const;

        /**
         * This is a function used for grading.
         * @param newOut The stream to print to.
         */
        void setOutput(ostream & newOut);

	private:

		Node* root;

		/**
		 * Private helper function for the public insert function.
		 * @param node The current node in the recursion
         * @param key The key to insert
         * @param value The value for the key to insert
		 */
		void insert(Node* & node, const K & key, const V & value);

        /**
         * Finds an element in the AVL tree.
         * @param node The node to search from (current subroot)
         * @param key The element to search for
         * @return the value stored for that key
         */
		V find(Node * node, const K & key) const;

		/**
		 * Rotates the tree right (there is an imbalance on the left side).
		 */
		void rotateRight(Node* & node);
		
        /**
		 * Rotates the tree left (there is an imbalance on the right side).
		 */
		void rotateLeft(Node* & node);
		
        /**
		 * A right left rotation.
         * This function should simply call rotateRight and rotateLeft.
		 */
		void rotateRightLeft(Node* & node);

		/**
		 * A left right rotation.
         * This function should simply call rotateLeft and rotateRight.
         * @param node The node to rotate
		 */
		void rotateLeftRight(Node* & node);

        /**
         * @param node The node's height to check
         * @return the height of the node if it's non-NULL or -1 if it is NULL
         */
		int heightOrNeg1(const Node* node) const;

		/**
		 * Helper function for operator= and cctor.
		 * @param subRoot The current node in the recursion
		 */
		Node* copy(const Node* subRoot);

		/**
		 * Private helper function for clear that clears beneath the parameter node.
		 * @param subRoot The current node in the recursion
		 */
		void clear(Node * subRoot);

        /** member variable used for grading */
        ostream* _out;
};

#include "avltree_given.cpp"
#include "avltree.cpp"
#endif
