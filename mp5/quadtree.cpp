// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"
//the default constructor
Quadtree::Quadtree(){
	root = NULL;
	upperHorizontal = 0;
	lowerHorizontal = 0;
	leftVertical = 0;
	rightVertical = 0;
}

Quadtree::Quadtree ( PNG const & source, int resolution){
	upperHorizontal = 0;
	lowerHorizontal = resolution;
	leftVertical = 0;
	rightVertical = resolution;
	root = constructQuadtree(source, upperHorizontal, lowerHorizontal, leftVertical, rightVertical);
}

Quadtree::~Quadtree (){
	clear();
}

Quadtree::Quadtree (Quadtree const &other){
	copy(other);
}

Quadtree const & Quadtree::operator= (Quadtree const &other){
	if(this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

void Quadtree::buildTree ( PNG const &  source,	int  resolution){
	clear();
	Quadtree(source, resolution);
}

RGBAPixel Quadtree::getPixel( int x, int y) const {
	RGBAPixel *tempPixel = new RGBAPixel();
	return *tempPixel;
}


PNG Quadtree::decompress()const{
	PNG* pngPtr = new PNG();
	return *pngPtr;
}

void Quadtree::clockwiseRotate(){
	return;
} 	

void Quadtree::prune(int tolerance){
	return;
} 	

int Quadtree::pruneSize(int	tolerance) const{
	return 0;
}

int Quadtree::idealPrune(int numLeaves) const{
	return 0;
}
//helper function
Quadtree::QuadtreeNode* Quadtree::constructQuadtree(source, UpperHorizontal, LowerHorizontal, LeftVertical, RightVertical){
	if(UpperHorizontal+1 == LowerHorizontal)
	{
	QuadtreeNode* croot = new QuadtreeNode();
	croot->nwChild = NULL;
	croot->neChild = NULL;
	croot->swChild = NULL;
	croot->seChild = NULL;
	croot->element = *source(LeftVertical, UpperHorizontal);
	return croot;
	}
	else
	{
	QuadtreeNode* croot = new QuadtreeNode();
	int d = LowerHorizontal - UpperHorizontal;
	croot->nwChild = constructQuadtree(source, UpperHorizontal, UpperHorizontal+d/2, LeftVertical+d/2, RightVertical);
	croot->neChild = constructQuadtree(source, UpperHorizontal, UpperHorizontal+d/2, LeftVertical, LeftVertical+d/2);
	croot->swChild = constructQuadtree(source, UpperHorizontal+d/2, LowerHorizontal, LeftVertical, LeftVertical+d/2);
	croot->seChild = constructQuadtree(source, UpperHorizontal+d/2, LowerHorizontal, LeftVertical+d/2, RightVertical);
	croot->element = *source(LeftVertical+d/2, UpperHorizontal+d/2);
	return croot;
	}

}

void clear(){
	clearTheRoot(root);
	root = NULL;	
}

void clearTheRoot( QuadtreeNode* croot){
	if(croot == NULL)
		return;
	clearTheRoot(croot->nwChild);
	clearTheRoot(croot->neChild);
	clearTheRoot(croot->swChild);
	clearTheRoot(croot->seChild);
	croot->nwChild = NULL;
	croot->neChild = NULL;
	croot->swChild = NULL;
	croot->seChild = NULL;
	delete croot;
}

void copy(other){
	root = copyTheRoot(other.root);
}

void copyTheRoot(QuadtreeNode* otherCroot){
	if(otherCroot == NULL)
		return NULL;
	QuadtreeNode* thisCroot = new QuadtreeNode(); 
	thisCroot->element = otherCroot->element;
	thisCroot->nwChild = copyTheRoot(otherCroot->nwChild);
	thisCroot->neChild = copyTheRoot(otherCroot->neChild);
	thisCroot->swChild = copyTheRoot(otherCroot->swChild);
	thisCroot->seChild = copyTheRoot(otherCroot->seChild);
	return thisCroot;

} 
