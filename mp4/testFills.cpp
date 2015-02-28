#include <limits.h>
#include <vector>
#include <sys/stat.h>
#include <iostream>
#include "png.h"
#include "filler.h"
#include "solidColorPicker.h"
#include "gridColorPicker.h"
#include "gradientColorPicker.h"
#include "rainbowColorPicker.h"

using namespace std;

#define FUNCTORTESTHEIGHT 60
#define FUNCTORTESTWIDTH 60
#define FUNCTORTESTFREQ 10
#define FUNCTORTESTX 40
#define FUNCTORTESTY 10
#define FUNCTORTESTRADIUS 35
#define FUNCTORTESTGRIDSPACING 8

#define SOLIDX 43
#define SOLIDY 15
#define SOLIDTOLERANCE 700
#define SOLIDTESTIMAGE "originals/solidTest.png"
#define SOLIDFRAMEFREQ 130

#define GRIDX 40
#define GRIDY 25
#define GRIDTOLERANCE 7000
#define GRIDTESTIMAGE "originals/gridTest.png"
#define GRIDFRAMEFREQ 20
#define GRIDGRIDSPACING 3

#define GRADIENTX 80
#define GRADIENTY 80
#define GRADIENTTOLERANCE 8500
#define GRADIENTTESTIMAGE "originals/gradientTest.png"
#define GRADIENTFRAMEFREQ 150 
#define GRADIENTRADIUS 25

PNG testColorPicker(colorPicker & picker) {
	PNG img;
	img.resize(FUNCTORTESTWIDTH, FUNCTORTESTHEIGHT);
	RGBAPixel px;

	for(int x = 1; x < FUNCTORTESTWIDTH; x = x + x)
	{
		for(int y = 1; y < FUNCTORTESTHEIGHT; y = y + y) {
			px = picker(x, y);
			cout << "\toperator()(" << x << ", " << y << ") = {" << (int)px.red << ", ";
			cout << (int)px.green << ", " << (int)px.blue << "}" << endl;
		}
	}

	for(int x = 0; x < FUNCTORTESTWIDTH; x++)
		for(int y = 0; y < FUNCTORTESTHEIGHT; y++)
			*img(x, y) = picker(x, y);

	return img;
}

void testSolidPicker() {
		RGBAPixel px;
		px.red = 255;
		px.blue = px.green = 100;
		solidColorPicker solidPicker(px);

		testColorPicker(solidPicker).writeToFile("images/solidColorPickerTest.png");
		cout << "\tWrote images/solidColorPickerTest.png" << endl;
}

void testGradientPicker() {
		RGBAPixel px1, px2;
		px1.red = 255;
		px1.blue = px1.green = 100;
		px2.blue = 255;
		px2.green = px2.red = 10;
		gradientColorPicker gradientPicker(px1, px2, FUNCTORTESTRADIUS, FUNCTORTESTX, FUNCTORTESTY);

		testColorPicker(gradientPicker).writeToFile("images/gradientColorPickerTest.png");
		cout << "\tWrote images/gradientColorPickerTest.png" << endl;
}

void testGridPicker() {
		RGBAPixel px1;
		px1.green = 255;
		px1.blue = px1.red = 110;
		gridColorPicker gridPicker(px1, FUNCTORTESTGRIDSPACING);

		testColorPicker(gridPicker).writeToFile("images/gridColorPickerTest.png");
		cout << "\tWrote images/gridColorPickerTest.png" << endl;
}

void testColorPickers() {
	cout << "Testing solidColorPicker:" << endl;
		testSolidPicker();
	cout << "Testing GradientColorPicker:" << endl;
		testGradientPicker();
	cout << "Testing GridColorPicker:" << endl;
		testGridPicker();
}

enum Filler {
    DFS, BFS
};

void testSolidFill( const Filler & filler, const string & outputFile ) {
	PNG img;
	img.readFromFile( SOLIDTESTIMAGE );
	RGBAPixel px( 70, 50, 13 );

    animation anim;
    if( filler == DFS )
        anim = filler::dfs::fillSolid( img, SOLIDX, SOLIDY, px, SOLIDTOLERANCE, SOLIDFRAMEFREQ );
    else
        anim = filler::bfs::fillSolid( img, SOLIDX, SOLIDY, px, SOLIDTOLERANCE, SOLIDFRAMEFREQ );
	anim.write( outputFile );
	cout << "\tWrote " << outputFile << endl;
}

void testSolidFills() {
	testSolidFill( DFS, "images/dfsSolidTest.gif" );
	testSolidFill( BFS, "images/bfsSolidTest.gif" );
}

void testGridFill( const Filler & filler, const string & outputFile ) {
	PNG img;
	img.readFromFile( GRIDTESTIMAGE );
	RGBAPixel px( 70, 25, 70 );

    animation anim;
    if( filler == DFS )
        anim = filler::dfs::fillGrid( img, GRIDX, GRIDY, px, GRIDGRIDSPACING, GRIDTOLERANCE, GRIDFRAMEFREQ );
    else
        anim = filler::bfs::fillGrid( img, GRIDX, GRIDY, px, GRIDGRIDSPACING, GRIDTOLERANCE, GRIDFRAMEFREQ );
	anim.write( outputFile );
	cout << "\tWrote " << outputFile << endl;
}

void testGridFills() {
	testGridFill( DFS, "images/dfsGridTest.gif" );
	testGridFill( BFS, "images/bfsGridTest.gif" );
}

void testGradientFill( const Filler & filler, const string & outputFile ) {
	PNG img;
	img.readFromFile( GRADIENTTESTIMAGE );
	RGBAPixel px;
	px.red = px.blue = 0;
	px.green = 25;
	RGBAPixel px2;
	px2.red = px2.blue = 200;
	px2.green = 25;

    animation anim;
    if( filler == DFS )
        anim = filler::dfs::fillGradient( img, GRADIENTX, GRADIENTY, px, px2, GRADIENTRADIUS, GRADIENTTOLERANCE, GRADIENTFRAMEFREQ );
    else
        anim = filler::bfs::fillGradient( img, GRADIENTX, GRADIENTY, px, px2, GRADIENTRADIUS, GRADIENTTOLERANCE, GRADIENTFRAMEFREQ );
	anim.write( outputFile );
	cout << "\tWrote " << outputFile << endl;
}

void testGradientFills() {
	testGradientFill( DFS, "images/dfsGradientTest.gif" );
	testGradientFill( BFS, "images/bfsGradientTest.gif" );
}

void pacmanTests() {
	cout << "Testing PacMan" << endl;

	// PAC MAN BFS
	PNG img;
	img.readFromFile("originals/pacMan.png");
	rainbowColorPicker BFSfiller(1.0/1000.0);
	animation pacManBFS = filler::bfs::fill(img, img.width()/2, img.height()/2,
	                               BFSfiller, 8000, INT_MAX);
	img.writeToFile("images/pacManBFS.png");
	cout << "\tWrote images/pacManBFS.png" << endl;
	//blueManBFS.write("pacManBFS.gif");

	// PAC MAN DFS
	img.readFromFile("originals/pacMan.png");
	rainbowColorPicker DFSfiller(1.0/1000.0);
	animation pacManDFS = filler::dfs::fill(img, img.width()/2, img.height()/2,
	                               DFSfiller, 8000, INT_MAX);
	img.writeToFile("images/pacManDFS.png");
	cout << "\tWrote images/pacManDFS.png" << endl;


	// Make ANTI image
	PNG antiImg;
	antiImg.readFromFile("originals/pacMan.png");
	RGBAPixel black;
	black.red = black.green = black.blue = 0;
	RGBAPixel grey;
	grey.red = grey.green = grey.blue = 1;
    filler::bfs::fillSolid(antiImg, 10, 10, grey, 8000, INT_MAX);
    filler::bfs::fillSolid(antiImg, antiImg.width()/2, antiImg.height()/2, black, 8000, INT_MAX);

	// ANTI PAC MAN BFS
	img = antiImg;
	rainbowColorPicker aBFSfiller(1.0/1000.0);
	animation aManBFS = filler::bfs::fill(img, 20, 20, aBFSfiller, 0, 2000);
	//img.writeToFile("antiPacManBFS.png");
	aManBFS.write("images/antiPacManBFS.gif");
	cout << "\tWrote images/antiPacManBFS.gif" << endl;

	// ANTI PAC MAN DFS
	img = antiImg;
	rainbowColorPicker aDFSfiller(1.0/1000.0);
	animation aManDFS = filler::dfs::fill(img, 20, 20, aDFSfiller, 0, 2000);
	//img.writeToFile("antiPacManDFS.png");
	aManDFS.write("images/antiPacManDFS.gif");
	cout << "\tWrote images/antiPacManDFS.gif" << endl;
}


void printUsage(char * arg)
{
	cout << "Usage:" << endl
		 << arg << " colorpickers" << endl
		 << arg << " grid" << endl
		 << arg << " solid" << endl
		 << arg << " gradient" << endl
		 << arg << " pacman" << endl
		 << arg << " all" << endl;
}

bool exists(const string & path)
{
	// Try stat-ing it
	struct stat st;
	if (stat(path.c_str(), &st) != 0) return false;
	// Check for read permission
	if ((st.st_mode & S_IRUSR) == 0) return false;

	// Check for correct file/directory nature
	if (path[path.length()-1] != '/') return S_ISREG(st.st_mode);

	// Otherwise we want a directory
	if ((st.st_mode & S_IXUSR) == 0) return false;
	return S_ISDIR(st.st_mode);
}

int main(int argc, char ** argv) {

	if (argc < 2)
	{
		printUsage(argv[0]);
		return 1;
	}

    vector<string> args(argv, argv + argc);

	bool colors = args[1] == "colorpickers";
	bool grid = args[1] == "grid";
	bool solid = args[1] == "solid";
	bool gradient = args[1] == "gradient";
	bool pacman = args[1] == "pacman";
	if (args[1] == "all") {
		colors = grid = solid = gradient = pacman = true;
	}

	if (!colors && !grid && !solid && !gradient && !pacman)
	{
		cout << "Invalid argument: " << argv[1] << endl;
		printUsage(argv[0]);
		return 1;
	}

	if (!exists("images/"))
		mkdir("images", 0700);

	//Testing the functors
	if (colors)
		testColorPickers();

	//Testing the fills themselves.  Note that this uses the functors, so make sure those
	//are working first
	if (solid) {
		cout << "Testing solid fills" << endl;
		testSolidFills();
	}

	if (grid) {
		cout << "Testing grid fills" << endl;
		testGridFills();
	}

	if (gradient) {
		cout << "Testing gradient fills" << endl;
		testGradientFills();
	}

	//Tests Pac-Man!
	if (pacman) {
		pacmanTests();
	}

	return 0;
}

