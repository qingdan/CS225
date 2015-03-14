#include <cstddef>
#include <cstdlib>
#include <iostream>

using namespace std;

#include "quadtree.h"
#include "png.h"

/**** Testing/grading functions ****/


// printTree (public interface)
//   - parameters: none
//   - prints the contents of the Quadtree using a preorder traversal
void Quadtree::printTree(ostream & out /* = cout */) const
{
	if (root == NULL)
	   out << "Empty tree.\n";
	else
	   printTree(out, root, 1);
}


// printTree (private helper)
//   - parameters: QuadtreeNode *current - pointer to the root of the
//                    subQuadtree which we wish to print
//                 int level - the current recursion depth; used for
//                    determining when to terminate recursion (see note below)
//   - prints the leaves of the Quadtree using a preorder traversal
void Quadtree::printTree(ostream & out, QuadtreeNode const * current, int level) const
{
	// Is this a leaf?
	// Note: it suffices to check only one of the child pointers,
	// since each node should have exactly zero or four children.
	if (current->neChild == NULL) {
	   out << current->element << " at depth " << level << "\n";
	   return;
	}

	// This clause added for the sake of grading; we will never call
	// printTree() on quadtrees larger than  128x128.  (This is a
	// necessary restriction, as the grading scripts choke on programs
	// which produce excessive amounts of output.)
	if (level > 7) {
	   out << "Error: infinite loop detected in printTree();"
	       << " quadtree has a loop.\n";
	   out << "Aborting program.\n";
	   exit(1);
	}

	// Standard preorder traversal
	printTree(out, current->neChild, level + 1);
	printTree(out, current->seChild, level + 1);
	printTree(out, current->swChild, level + 1);
	printTree(out, current->nwChild, level + 1);
}


// operator==
//   - parameters: Quadtree const & other - reference to a const Quadtree
//                    object, against which the current Quadtree will be
//                    compared
//   - return value: a boolean which is true if the Quadtrees are deemed
//        "equal", and false otherwise
//   - compares the current Quadtree with the parameter Quadtree, and
//        determines whether or not the two are the same
// Note: this method relies on the private helper method compareTrees()
bool Quadtree::operator==(Quadtree const & other) const
{
	return compareTrees(root, other.root);
}


// compareTrees
//   - parameters: QuadtreeNode const * firstPtr - pointer to the root
//                    of a subtree of the "first" Quadtree under
//                    consideration
//                 QuadtreeNode const * secondPtr - pointer to the root
//                    of a subtree of the "second" Quadtree under
//                    consideration
//   - return value: a boolean which is true if the subQuadtrees are deemed
//        "equal", and false otherwise
//   - compares the subQuadtree rooted at firstPtr with the subQuadtree
//        rooted at secondPtr, and determines whether the two are the same
//   - this function only compares the leaves of the trees, as we did not
//     impose any requirements on what you should do with interior nodes
bool Quadtree::compareTrees(QuadtreeNode const * firstPtr,
	                        QuadtreeNode const * secondPtr) const
{
	if (firstPtr == NULL && secondPtr == NULL)
	   return true;

	if (firstPtr == NULL || secondPtr == NULL)
	   return false;

	// if they're both leaves, see if their elements are equal
	// note: child pointers should _all_ either be NULL or non-NULL,
	// so it suffices to check only one of each
	if (firstPtr->neChild == NULL && secondPtr->neChild == NULL) {
	   if (firstPtr->element.red != secondPtr->element.red ||
	      firstPtr->element.green != secondPtr->element.green ||
	      firstPtr->element.blue != secondPtr->element.blue)
	      return false;
	   else
	      return true;
	}

	// they aren't both leaves, so recurse
	return (compareTrees(firstPtr->neChild, secondPtr->neChild) &&
	        compareTrees(firstPtr->nwChild, secondPtr->nwChild) &&
	        compareTrees(firstPtr->seChild, secondPtr->seChild) &&
	        compareTrees(firstPtr->swChild, secondPtr->swChild));
}


