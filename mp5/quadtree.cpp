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
Quadtree::Quadtree()
{
	root = NULL;
	upperHorizontal = 0;
	lowerHorizontal = 0;
	leftVertical = 0;
	rightVertical = 0;
}

Quadtree::Quadtree ( PNG const & source, int resolution)
{
	upperHorizontal = 0;
	lowerHorizontal = resolution;
	leftVertical = 0;
	rightVertical = resolution;
	root = constructQuadtree(source, upperHorizontal, lowerHorizontal, leftVertical, rightVertical);
}

Quadtree::~Quadtree ()
{
	clear();
}

Quadtree::Quadtree (Quadtree const &other)
{
	copy(other);
}

Quadtree const & Quadtree::operator= (Quadtree const &other)
{
	if(this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

void Quadtree::buildTree ( PNG const &  source,	int  resolution)
{
	clear();
	upperHorizontal = 0;
	lowerHorizontal = resolution;
	leftVertical = 0;
	rightVertical = resolution;
	root = constructQuadtree(source, upperHorizontal, lowerHorizontal, leftVertical, rightVertical);
}

RGBAPixel Quadtree::getPixel( int x, int y) const 
{
	if(x<0||x>=rightVertical||y<0||y>=lowerHorizontal||root==NULL)
	{
		RGBAPixel tempPixel;
		return tempPixel;
	}
	QuadtreeNode* curr = help_getPixel(x,y,0,rightVertical,0,lowerHorizontal,root);
	return curr->element;
}


PNG Quadtree::decompress()const
{
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

void Quadtree::clockwiseRotate()
{
	helpRotation(root);	
	return;
} 	

void Quadtree::prune(int tolerance)
{
	helpPrune(root, tolerance);
	return;
} 	

int Quadtree::pruneSize(int tolerance) const{
	Quadtree* tempTree = new Quadtree(*this);
	tempTree->prune(tolerance);
	int result = countNodes(tempTree->root);	
	tempTree->clear();
	tempTree = NULL;
	return result;
}

int Quadtree::idealPrune(int numLeaves) const{
	int maxTolerance = 300;
	while(pruneSize(maxTolerance)<=numLeaves)
		maxTolerance += 300;
	return findIdeal(maxTolerance-300, maxTolerance, numLeaves);
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
	croot = NULL;
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
			//std::cout<<"test"<<endl;
	if(x<leftBoundary+d/2&&y<upBoundary+d/2)		
	   {//std::cout<<"test1"<<endl; 
	return help_getPixel(x,y,leftBoundary,leftBoundary+d/2,upBoundary,upBoundary+d/2,curr->nwChild);}
	else if(x>=leftBoundary+d/2&&y<upBoundary+d/2)		
		return help_getPixel(x,y,leftBoundary+d/2,rightBoundary,upBoundary,upBoundary+d/2,curr->neChild);
	else if(x<leftBoundary+d/2&&y>=upBoundary+d/2)	
		return help_getPixel(x,y,leftBoundary,leftBoundary+d/2,upBoundary+d/2,downBoundary,curr->swChild);
	else
		return help_getPixel(x,y,leftBoundary+d/2,rightBoundary,upBoundary+d/2,downBoundary,curr->seChild);
}

void Quadtree::helpRotation(QuadtreeNode* currNode)
{
	QuadtreeNode * hold1 = currNode->neChild;//hold 1
	QuadtreeNode * hold2 = currNode->nwChild;//hold 2
	QuadtreeNode * hold3 = currNode->swChild;//hold 1
	QuadtreeNode * hold4 = currNode->seChild;//hold 2
	currNode->neChild = hold2;
	currNode->nwChild = hold3;
	currNode->swChild = hold4;
	currNode->seChild = hold1;
	hold1 = NULL;
	hold2 = NULL;
	hold3 = NULL;
	hold4 = NULL;
	if(currNode->nwChild != NULL)
	{
		helpRotation(currNode->neChild);
		helpRotation(currNode->nwChild);
		helpRotation(currNode->swChild);
		helpRotation(currNode->seChild);		
	}
	
}

void Quadtree::helpPrune(QuadtreeNode* currNode, int tolerance)
{
	if(currNode->neChild == NULL)
		return;
	if(checkNode(currNode, currNode, tolerance))
	{
		clearTheRoot(currNode->neChild);
		currNode->neChild = NULL;
		clearTheRoot(currNode->nwChild);
		currNode->nwChild = NULL;
		clearTheRoot(currNode->swChild);
		currNode->swChild = NULL;
		clearTheRoot(currNode->seChild);
		currNode->seChild = NULL;
		return;
	}
	else
	{
		helpPrune(currNode->neChild, tolerance);
		helpPrune(currNode->nwChild, tolerance);
		helpPrune(currNode->swChild, tolerance);
		helpPrune(currNode->seChild, tolerance);
		return;
	}
}

bool Quadtree::checkNode(QuadtreeNode* OriginNode, QuadtreeNode* currNode, int tolerance)
{
	if(currNode->neChild == NULL)
		return meetPrune(OriginNode, currNode,  tolerance);
	if(!checkNode(OriginNode, currNode->nwChild, tolerance))
		return false;
	else if(!checkNode(OriginNode, currNode->neChild, tolerance))
		return false;
	else if(!checkNode(OriginNode, currNode->swChild, tolerance))
		return false;
	else if(!checkNode(OriginNode, currNode->seChild, tolerance))
		return false;
	else
		return true;
}
bool Quadtree::meetPrune(QuadtreeNode* oneNode, QuadtreeNode* otherNode, int tolerance)
{
	int diffRed = oneNode->element.red-otherNode->element.red;
	int diffGreen = oneNode->element.green-otherNode->element.green;	
	int diffBlue = oneNode->element.blue-otherNode->element.blue;
	if(diffRed*diffRed+diffGreen*diffGreen+diffBlue*diffBlue <= tolerance)
		return true;
	else
		return false;
}

int Quadtree::countNodes(QuadtreeNode* theNode) const
{
	if(theNode->neChild == NULL)
		return 1;
	return (countNodes(theNode->neChild)+countNodes(theNode->nwChild)+countNodes(theNode->swChild)+countNodes(theNode->seChild));
}

int Quadtree::findIdeal(int minTolerance, int maxTolerance, int numLeaves) const
{
	int midTolerance = (minTolerance+maxTolerance)/2;
	int resultOfMid = pruneSize(midTolerance);
	int resultOfMidMi = pruneSize(midTolerance-1);
	if(resultOfMid<=numLeaves&&resultOfMidMi>numLeaves)
		return midTolerance;
	if(maxTolerance  == midTolerance)
			return midTolerance-1;
	if(resultOfMid <= numLeaves)
		return findIdeal(minTolerance, midTolerance-1, numLeaves);
	else
		return findIdeal(midTolerance+1, maxTolerance, numLeaves);
}

/*bool Quadtree::testIdeal(int testTolerance, int numLeaves)
{
	int result = pruneSize(testTolerance);
	int resultMi = pruneSize(testTolerance-1);
	if(result<=numLeaves&&resultMi>numLeaves)
		return true;
	else
		return false;
}*/
