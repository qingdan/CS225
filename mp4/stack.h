/**
 * @file stack.h
 * Definition of the Stack class.
 *
 * You **should not** modify this file for the MP!
 *
 * @author CS 225 course staff
 * @date Spring 2007
 *
 * @author Daniel Hoodin
 * @date Spring 2008
 *
 * @author Chase Geigle
 * @date Fall 2012
 */
#ifndef STACK_H
#define STACK_H

#include <list>
using std::list;

#include "ordering_structure.h"

/**
 * Stack class: represents a standard stack. Templated to hold elements of
 * any type.
 *
 * You **should not** modify this file for the MP!
 *
 * @author CS 225 course staff
 * @date Spring 2007
 *
 * @author Daniel Hoodin
 * @date Spring 2008
 *
 * @author Chase Geigle
 * @date Fall 2012
 */
template<class T>
class Stack : public OrderingStructure<T> {
	public:
		/**
		 * Adds the parameter object to the top of the Stack. That is, the
		 * element should go at the beginning of the list.
		 *
		 * @note This function must be O(1)!
		 *
		 * @param newItem The object to be added to the Stack.
		 */
		void push( const T & newItem );

		/**
		 * Removes the object on top of the Stack, and returns it. That is,
		 * remove the element at the beginning of the list. You may assume
		 * this function is only called when the Stack is not empty.
		 *
		 * @note This function must be O(1)!
		 *
		 * @return The element that used to be at the top of the Stack.
		 */
		T pop();

        /**
         * Adds an element to the ordering structure.
         *
         * @see OrderingStructure::add()
         */
        void add( const T & theItem );

        /**
         * Removes an element from the ordering structure.
         *
         * @see OrderingStructure::remove()
         */
        T remove();

		/**
		 * Finds the object on top of the Stack, and returns it to the caller. 
		 * Unlike pop(), this operation does not alter the Stack itself. It
		 * should look at the beginning of the list. You may assume this
		 * function is only called when the Stack is not empty.
		 *
		 * @note This function must be O(1)!
		 *
		 * @return The element at the top of the Stack.
		 */
		T peek();

		/** 
         * Determines if the Stack is empty.
		 *
		 * @note This function must be O(1)!
		 *
		 * @return Whether or not the stack is empty (bool).
		 */
		bool isEmpty() const;

	private:
		list<T> myStack; /**< The list representing our Stack: the front of the list
						      corresponds to the top of the Stack. 
							  @see http://www.cplusplus.com/reference/stl/list/ */
};

#include "stack.cpp"  // needed for template instantiation
#endif
