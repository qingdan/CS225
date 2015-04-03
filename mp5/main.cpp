#include <iostream>
#include "png.h"
#include "quadtree.h"

using std::cout;
using std::endl;

int main() {

   PNG imgIn, imgOut, imgOut2;
   imgIn.readFromFile("in.png");
   //imgIn.writeToFile("in_out.png");
   //imgIn.writeToFile("in_out.png");
   // test constructor, decompress
   Quadtree halfTree(imgIn, 0);
   imgOut = halfTree.decompress();
   imgOut.writeToFile("outHalf.png");

   // now for the real tests
   Quadtree fullTree;
   fullTree.buildTree(imgIn, 256);
   //fullTree = halfTree;
   // you may want to experiment with different commands in this section
	//fullTree.prune(1000);
   imgOut2 = fullTree.decompress();
  imgOut2.writeToFile("full.png");		
   // test pruneSize and idealPrune (slow in valgrind, so you may want to
   // comment these out when doing most of your testing for memory leaks)
   /*cout << "fullTree.pruneSize(0) = " << fullTree.pruneSize(0) << endl;
   cout << "fullTree.pruneSize(100) = " << fullTree.pruneSize(100) << endl;
   cout << "fullTree.pruneSize(1000) = " << fullTree.pruneSize(1000) << endl;
   cout << "fullTree.pruneSize(299) = " << fullTree.pruneSize(299) << endl;*/

   cout << "fullTree.idealPrune(0) = "  << fullTree.idealPrune(0) << endl;
   cout << "fullTree.idealPrune(10000000) = " << fullTree.idealPrune(10000000) << endl;


   // Test some creation/deletion functions
   Quadtree fullTree2;
   fullTree2 = fullTree;
   imgOut = fullTree2.decompress();
   imgOut.writeToFile("outCopy.png");


   // test clockwiseRotate
   halfTree.clockwiseRotate();
   imgOut = halfTree.decompress();
   imgOut.writeToFile("outRotated.png");


   // test prune
   fullTree = halfTree;
   fullTree.prune(1000);
   imgOut = fullTree.decompress();
   imgOut.writeToFile("outPruned.png");


   // test several functions in succession
   Quadtree fullTree3(fullTree);
   fullTree3.clockwiseRotate();
   fullTree3.prune(10000);
   fullTree3.clockwiseRotate();
   fullTree3.clockwiseRotate();
   fullTree3.clockwiseRotate();
   imgOut = fullTree3.decompress();
   imgOut.writeToFile("outEtc.png");

   // ensure that printTree still works
//   Quadtree tinyTree(imgIn, 4);
 //  cout << "Printing tinyTree:\n";
//	tinyTree.printTree();
 /*  tinyTree.prune(100);
	cout << "Printing tinyTree:\n";
   tinyTree.printTree();*/

   return 0;
}
