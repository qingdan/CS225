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
	middleHorizontal = resolution/2;
	lowerHorizontal = resolution;
	leftVertical = 0;
	middleVertical = resolution/2;
	rightVertical = resolution;
	root = constructQuadtree(source, upperHorizontal, lowerHorizontal, leftVertical, rightVertical);
}

Quadtree::~Quadtree (){
	clear();
}

Quadtree::Quadtree (Quadtree const &other){
	copy(other);
}

Quadtree const & operator= (Quadtree const &other){
	if(this == other)
		return;
	clear();
	copy(other);
	return this*;
}

void Quadtree::buildTree ( PNG const &  source,	int  resolution){
	clear();
	Quadtree(source, resolution);
}
PNG decompress()const{
	PNG* pngPtr = new PNG();
	return *pngPtr
}

//helper function
QuadtreeNode* Quadtree::constructQuadtree(source, upperHorizontal, lowerHorizontal, leftVertical, rightVertical){
	if(upperHorizontal+1 == lowerHorizontal)
	{
	QuadtreeNode* croot = new QuadtreeNode();
	croot->nwChild = NULL;
	croot->neChild = NULL;
	croot->swChild = NULL;
	croot->seChild = NULL;
	croot->element = *source(leftVertical, upperHorizontal);
	return croot;
	}
	else
	{
	QuadtreeNode* croot = new QuadtreeNode();
	int d = lowerHorizontal - upperHorizontal;
	croot->nwChild = constructQuadtree(source, upperHorizontal, upperHorizontal+d/2, leftVertical+d/2, rightVertical);
	croot->neChild = constructQuadtree(source, upperHorizontal, upperHorizontal+d/2, leftVertical, leftVertical+d/2);
	croot->swChild = constructQuadtree(source, upperHorizontal+d/2, lowerHorizontal, leftVertical, leftVertical+d/2);
	croot->seChild = constructQuadtree(source, upperHorizontal+d/2, lowerHorizontal, leftVertical+d/2, rightVertical);
	croot->element = *source(leftVertical+d/2, upperHorizontal+d/2);
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
