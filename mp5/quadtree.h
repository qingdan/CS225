// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	public:
	//the default constructor
	Quadtree(); 
	//the constructor with two arguments	
	Quadtree ( PNG const & source, int resolution); 
	//desctructor
	~Quadtree ();
	//copy constructor
	Quadtree (Quadtree const &other);
	//assign operator
	Quadtree const & operator= (Quadtree const &other);
	//Deletes the current contents of this Quadtree object, then turns 
	//it into a Quadtree object representing the upper-left d by d block of source. 
	void buildTree ( PNG const & source, int resolution);	
	//returns The pixel at the given (x, y) location 
	RGBAPixel getPixel( int x, int y) const;
	//Returns the underlying PNG object represented by the Quadtree. 	
	PNG decompress()const;

	void clockwiseRotate();

	void prune(int tolerance);

	int pruneSize(int tolerance) const;
	
	int idealPrune(int numLeaves) const;
	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		RGBAPixel element;  // the pixel stored as this node's "data"
	};
	
	QuadtreeNode* root;    // pointer to root of quadtree
	
	int upperHorizontal;
	int lowerHorizontal;
	int leftVertical;
	int rightVertical;

	//helper functions
	QuadtreeNode* constructQuadtree(PNG const & source, int upYaxis, int downYaxis, int leftXaxis, int rightXaxis);
	void clear();
	void clearTheRoot( QuadtreeNode* croot);
	void copy( const Quadtree & other );
	QuadtreeNode* copyTheRoot(QuadtreeNode* otherCroot);
	QuadtreeNode* help_getPixel(int x, int y, int leftBoundary, int rightBoundary, int upBoundary, int downBoundary, QuadtreeNode* curr) const;
	void helpRotation(QuadtreeNode* currNode);
	void helpPrune(QuadtreeNode* currNode, int tolerance);
	bool checkNode(QuadtreeNode* OriginNode, QuadtreeNode* currNode, int tolerance);
	bool meetPrune(QuadtreeNode* oneNode, QuadtreeNode* otherNode, int tolerance);
	int countLeaves(QuadtreeNode* theNode) const;
	int findIdeal(int minTolerance, int maxTolerance, int numLeaves) const;
	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};
#endif
