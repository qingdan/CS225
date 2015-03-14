
	/**** Functions added for testing/grading ****/

	public:
	// printTree (public interface)
	//   - parameters: none
	//   - prints the leaves of the Quadtree using a preorder traversal
	void printTree(std::ostream & out = std::cout) const;

	// operator==
	//   - parameters: Quadtree const & other - reference to a const Quadtree
	//                    object, against which the current Quadtree will be
	//                    compared
	//   - return value: a boolean which is true if the Quadtrees are deemed
	//        "equal", and false otherwise
	//   - compares the current Quadtree with the parameter Quadtree, and
	//        determines whether or not the two are the same
	// Note: this method relies on the private helper method compareTrees()
	bool operator==(Quadtree const & other) const;

	private:
	// printTree (private helper)
	//   - parameters: QuadtreeNode *current - pointer to the root of the
	//                    subQuadtree which we wish to print
	//                 int level - the current recursion depth; used for
	//                    determining when to terminate recursion (see note below)
	//   - prints the contents of the Quadtree using a preorder traversal
	void printTree(std::ostream & out, QuadtreeNode const *current, int level) const;

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
	bool compareTrees(QuadtreeNode const *firstPtr, QuadtreeNode const *secondPtr) const;

	public:

