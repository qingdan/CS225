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
	upperHorizontal = 0;
	lowerHorizontal = resolution;
	leftVertical = 0;
	rightVertical = resolution;
	root = constructQuadtree(source, upperHorizontal, lowerHorizontal, leftVertical, rightVertical);
}

RGBAPixel Quadtree::getPixel( int x, int y) const {
	if(x<0||x>=rightVertical||y<0||y>=lowerHorizontal||root==NULL)
	{
		RGBAPixel tempPixel;
		return tempPixel;
	}
	QuadtreeNode* curr = help_getPixel(x,y,0,rightVertical,0,lowerHorizontal,root);
	return curr->element;
}


PNG Quadtree::decompress()const{
	if(root == NULL)
	{
		PNG tempPicture;
		return tempPicture;
	}
	PNG::PNG tempPicture(rightVertical, lowerHorizontal);
	for(int x = 0; x < rightVertical; x++)
	{
		for(int y = 0; y < lowerHorizontal; y++)
		{
			*tempPicture(x,y) = getPixel(x,y);
		}
	}
	return tempPicture;
}

void Quadtree::clockwiseRotate(){
	return;
} 	

void Quadtree::prune(int tolerance){
	return;
} 	

int Quadtree::pruneSize(int tolerance) const{
	return 0;
}

int Quadtree::idealPrune(int numLeaves) const{
	return 0;
}
//helper function
Quadtree::QuadtreeNode* Quadtree::constructQuadtree(PNG const & source, int upYaxis, int downYaxis, int leftXaxis, int rightXaxis){
	if(upYaxis+1 == downYaxis)
	{
	QuadtreeNode* croot = new QuadtreeNode();
	croot->nwChild = NULL;
	croot->neChild = NULL;
	croot->swChild = NULL;
	croot->seChild = NULL;
	croot->element = *source(leftXaxis, upYaxis);
	return croot;
	}
	else
	{
	QuadtreeNode* croot = new QuadtreeNode();
	int d = downYaxis - upYaxis;
	croot->nwChild = constructQuadtree(source, upYaxis, upYaxis+d/2, leftXaxis, leftXaxis+d/2);
	croot->neChild = constructQuadtree(source, upYaxis, upYaxis+d/2, leftXaxis+d/2, rightXaxis);
	croot->swChild = constructQuadtree(source, upYaxis+d/2, downYaxis, leftXaxis, leftXaxis+d/2);
	croot->seChild = constructQuadtree(source, upYaxis+d/2, downYaxis, leftXaxis+d/2, rightXaxis);
	croot->element.red = (croot->nwChild->element.red+croot->neChild->element.red+croot->swChild->element.red+croot->seChild->element.red)/4;
	croot->element.green = (croot->nwChild->element.green+croot->neChild->element.green+croot->swChild->element.green+croot->seChild->element.green)/4;
	croot->element.blue = (croot->nwChild->element.blue+croot->neChild->element.blue+croot->swChild->element.blue+croot->seChild->element.blue)/4;
	croot->element.alpha = (croot->nwChild->element.alpha+croot->neChild->element.alpha+croot->swChild->element.alpha+croot->seChild->element.alpha)/4;
	return croot;
	}

}

void Quadtree::clear(){
	clearTheRoot(root);
	root = NULL;	
}

void Quadtree::clearTheRoot( QuadtreeNode* croot){
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

void Quadtree::copy(const Quadtree & other){
	upperHorizontal = other.upperHorizontal;
	lowerHorizontal = other.lowerHorizontal;
	leftVertical = other.leftVertical;
	rightVertical = other.rightVertical;	
	root = copyTheRoot(other.root);
}

Quadtree::QuadtreeNode* Quadtree::copyTheRoot(QuadtreeNode* otherCroot){
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

Quadtree::QuadtreeNode* Quadtree::help_getPixel(int x, int y, int leftBoundary, int rightBoundary, int upBoundary, int downBoundary, QuadtreeNode* curr) const {
	if(curr->nwChild == NULL)
		return curr;
	int d = rightBoundary - leftBoundary;
	if(x<leftBoundary+d/2&&y<upBoundary+d/2)		
		return help_getPixel(x,y,leftBoundary,leftBoundary+d/2,upBoundary,upBoundary+d/2,curr->nwChild);
	else if(x>=leftBoundary+d/2&&y<upBoundary+d/2)		
		return help_getPixel(x,y,leftBoundary+d/2,rightBoundary,upBoundary,upBoundary+d/2,curr->neChild);
	else if(x<leftBoundary+d/2&&y>=upBoundary+d/2)	
		return help_getPixel(x,y,leftBoundary,leftBoundary+d/2,upBoundary+d/2,downBoundary,curr->swChild);
	else
		return help_getPixel(x,y,leftBoundary+d/2,rightBoundary,upBoundary+d/2,downBoundary,curr->seChild);
}
