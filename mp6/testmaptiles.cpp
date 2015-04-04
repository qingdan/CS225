/**
 * @file testmaptiles.cpp
 * Runs the maptiles function to test it on some simple tiles.
 */

#include "maptiles.h"

/**
 * Test mapTiles function on a list of several valid tiles
 */
int main()
{
	PNG sourcePNG("testsource.png");
	SourceImage source(sourcePNG, 8);

	vector<TileImage> tileList;
	PNG a(1,1);
	PNG b(1,1);
	PNG c(1,1);
	*a(0,0) = RGBAPixel(255, 0, 0);
	*b(0,0) = RGBAPixel(0, 255, 0);
	*c(0,0) = RGBAPixel(0, 0, 255);
	tileList.push_back(TileImage(a));
	tileList.push_back(TileImage(b));
	tileList.push_back(TileImage(c));

	MosaicCanvas* canvas = mapTiles(source, tileList);
	if (canvas == NULL)
	{
		cerr << "ERROR: Returned NULL MosaicCanvas when shouldn't have" << endl;
		exit(1);
	}

	PNG actualImage = canvas->drawMosaic(10);

	actualImage.writeToFile("testmaptiles.png");

	delete canvas;
}

