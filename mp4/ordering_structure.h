/**
 * @file ordering_structure.h
 * Definition of an abstract ordering structure class.
 *
 * You **should not** modify this file for the MP.
 *
 * @author Chase Geigle
 * @date Fall 2012
 */
#ifndef _ORDERING_STRUCTURE_H_
#define _ORDERING_STRUCTURE_H_

/**
 * OrderingStructure: represents an interface for a structure that orders
 * items placed into it. Your Stack and Queue classes will implement this
 * interface.
 *
 * @author Chase Geigle
 * @date Fall 2012
 */
template <class T>
class OrderingStructure {
    public:
        /**
         * Destructor for the OrderingStructure. Virtual so as to allow
         * derived classes to override if necessary.
         */
        virtual ~OrderingStructure() {
            // nothing
        }

        /**
         * Adds the given element to the ordering structure.
         *
         * @param theItem The item to be added.
         */
        virtual void add( const T & theItem ) = 0;

        /**
         * Removes an element from the ordering structure. You may assume
         * that this function is only called when the ordering structure is
         * not empty.
         *
         * @return An element from the ordering structure.
         */
        virtual T remove() = 0;

        /**
         * Looks at the next element of the ordering structure, but does
         * not remove it.
         *
         * @return The next element on the ordering structure.
         */
        virtual T peek() = 0;

        /**
         * Determines if the ordering structure is empty.
         *
         * @return Whether or not there are still elements in the ordering
         *  structure.
         */
        virtual bool isEmpty() const = 0;
};
#endif
