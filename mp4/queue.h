/**
 * @file queue.h
 * Definition of the Queue class.
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
#ifndef QUEUE_H
#define QUEUE_H

#include "ordering_structure.h"
#include "stack.h"

/**
 * Queue class: represents a standard queue. Templated to hold elements of
 * any type. **You must only use the two private member Stacks as your
 * storage space! You cannot create new private member variables to hold
 * your objects!** It is up to you to determine how to use them, however.
 * 
 * Your Queue class should have O(1) running time over n operations
 * (amortized). There is an obvious solution that takes O(n) running time,
 * but this will not recieve all of the available points.
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
class Queue : public OrderingStructure<T> {
	public:
		/**
		 * Adds the parameter object to the back of the Queue.
		 * 
		 * @note This fuction should have O(1) behavior over n operations!
		 *
		 * @param newItem object to be added to the Queue.
		 */
		void enqueue( const T & newItem );

		/**
		 * Removes the object at the front of the Queue, and returns it to
		 * the caller. You may assume that this function is only called
		 * when the Queue is non-empty.
		 *
		 * @note This function should have O(1) behavior over n operations!
		 *
		 * @return The item that used to be at the front of the Queue.
		 */
		T dequeue();

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
		 * Finds the object at the front of the Queue, and returns it to
		 * the caller. Unlike pop(), this operation does not alter the
		 * queue. You may assume that this function is only called when the
		 * Queue is non-empty.
		 *
		 * @note This function should have O(1) behavior over n operations!
		 *
		 * @return The item at the front of the queue.
		 */
		T peek();

		/**
		 * Determines if the Queue is empty.
		 *
		 * @note This function should have O(1) behavior over n operations!
		 *
		 * @return bool which is true if the Queue is empty, false
		 *	otherwise.
		 */
		bool isEmpty() const;

	private:
		Stack<T> inStack;  /**< One of the two Stack objects you must use. */
		Stack<T> outStack; /**< The other of the two Stack objects you must use. */
};
#include "queue.cpp"
#endif
