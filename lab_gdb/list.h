/**
 * @file list.h
 * Singly Linked List (Lab GDB).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 *
 * @author Veer Dedhia
 * @date (modified) Spring 2014
 */
#ifndef _LIST_H_
#define _LIST_H_

#include <iterator>
#include <ostream>
#include <algorithm>

using namespace std;

/**
 * List: This is a templated linked list class (meaning it contains data of
 * templated type T, which is a placeholder for a type).
 *
 * You should NOT remove anything from this class definition.
 * You should NOT modify this file.
 */
template <class T>
class List
{
    private:
        /**
         * The ListNode class is private to the List class via the principle of
         * encapsulation---the end user does not need to know our node-based
         * implementation details.
         */
        class ListNode
        {
            public:
                /**
                 * Default ListNode constructor.
                 * Implemented for you.
                 * @see list_given.cpp
                 */
                ListNode();

                /**
                 * Constructs a ListNode with the given data.
                 * Implemented for you.
                 * @see list_given.cpp
                 */
                ListNode( const T & ndata );

                /**
                 * A pointer to the next node in the list. May be NULL
                 * if one does not exist.
                 */
                ListNode * next;

                /**
                 * The data contained in this node. We do not allow you to
                 * modify node data, so it is const.
                 */
                const T data;
        };

    public:
        /**
         * Default List constructor. 
         * Creates an empty List.
         * @see list_given.cpp
         */
        List();

        /**
         * Copy constructor for a List. 
         * Since Lists allocate dynamic memory (i.e., they use "new", we
         * must define the Big Three).
         * @see list_given.cpp
         *
         * @param other The list we are copying.
         */
        List( const List<T> & other ); 

        /**
         * Overloaded assignment operator for Lists.
         * Part of the Big Three that we must define because the class
         * allocates dynamic memory.
         * @see list_given.cpp
         *
         * @param rhs The right hand side of the assignment statement.
         */
        List<T> & operator=( const List<T> & rhs );

        /**
         * Gets the size of the List.
         * Defined as a const function because it promises not to modify 
         * the current List in any way.
         * @see list_given.cpp
         *
         * @return The size of the current List.
         */
        int size() const;

        /**
         * Used to print the list. 
         * Const because it promises not to modify the current List.
         * @see list_given.cpp
         *
         * @param os Output stream to print the list to (e.g. cout)
         */
        void print( ostream & os ) const;

        /**
         * Determines if the current List is empty. 
         * Const because it promises not to modify the current List.
         * @see list_given.cpp
         *
         * @return Boolean value of whether the current List is empty.
         */
        bool empty() const;

        /**
         * Destroys the current List. This function should ensure that
         * memory does not leak on destruction of a list.
         */
        ~List();

        /**
         * Inserts a new node at the front of the List.
         * This function **SHOULD** create a new ListNode.
         *
         * @param ndata The data to be inserted.
         */
        void insertFront( const T & ndata );

        /**
         * Inserts a new node at the back of the List.
         * This function **SHOULD** create a new ListNode.
         *
         * @param ndata The data to be inserted.
         */
        void insertBack( const T & ndata );

        /**
         * Reverses the current List.
         */
        void reverse();

        /**
         * Shuffles the current list by applying a perfect shuffle once.
         */
        void shuffle();

        // Provided Iterator Functions, don't remove
        #include "list_given.h"

    private:
        /*
         * Private member variables.
         *
         * You must use these as specified in the spec and may not rename them.
         */

        /**
         * The head of the List. May be NULL if the List is empty.
         */
        ListNode * head;

        /**
         * The length of the current List. Do not forget to update it!
         */
        int length;

        /*
         * Private helper functions.
         */

        /**
         * Copies the given list into the current list.
         * @see list_given.cpp
         * @param other The List to be copied.
         */
        void copy( const List<T> & other ); // implemented in list_given.cpp

        /**
         * Destroys all dynamically allocated memory associated with the
         * current List class.
         */
        void clear();

        /**
         * Helper function to recursively reverse the enitre sequence of
         * linked memory inside a List.
         *
         * @param curr A pointer to the current list node we are reversing.
         * @param prev A pointer to the node that should come before the
         * current node in the final reversed list.
         */
        ListNode * reverse( ListNode * curr, ListNode * prev, int len );
};

// needed for template instantiation
#include "list.cpp"

// this includes all of the functions that are given to you
// (i.e., the ones that you do not need to implement)
#include "list_given.cpp"

#endif
