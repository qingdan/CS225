/**
 * sourceimage.h
 *
 * SourceImage extends the Image class and provides some additional data and
 * functions suitable for the source image for the photomosaic.  The default
 * constructor will take a number of rows and columns to divide the image
 * into.  The image will then be processes to find the average color of each
 * region.
 *
 * Authors:
 * Jack Toole
 * Matt Sachtler
 * Scott Wegner
 *
 * Developed for CS225 PhotoMosaic MP, Fall 2008
 * Rewritten Fall 2011 by Jack Toole
 */

#include <algorithm>
#include <cmath>
#include <iostream>

#include "sourceimage.h"

using namespace std;

SourceImage::SourceImage(const PNG & image, int setResolution)
	: backingImage(image), resolution(setResolution)
{
	if (resolution< 1)
	{
		cerr << "ERROR: resolution set to < 1. Aborting." << endl;
		exit(-1);
	}
	
	resolution = min(backingImage.width(), backingImage.height());
	resolution = min(resolution, setResolution);
}

RGBAPixel SourceImage::getRegionColor(int row, int col) const
{
	int width  = backingImage.width();
	int height = backingImage.height();

	int startX = divide(width  *  col,    getColumns());
	int endX   = divide(width  * (col+1), getColumns());
	int startY = divide(height *  row,    getRows());
	int endY   = divide(height * (row+1), getRows());

	uint64_t r = 0;
	uint64_t g = 0;
	uint64_t b = 0;

	for (int y = startY; y < endY; y++)
	{
		for (int x = startX; x < endX; x++)
		{
			r += backingImage(x, y)->red;
			g += backingImage(x, y)->green;
			b += backingImage(x, y)->blue;
		}
	}

	RGBAPixel color;
	uint64_t numPixels = (endX - startX) * (endY - startY);
	color.red   = divide(r, numPixels);
	color.green = divide(g, numPixels);
	color.blue  = divide(b, numPixels);
	return color;
}

int SourceImage::getRows() const
{
	if (backingImage.height() <= backingImage.width())
		return resolution;
	else
		return divide(resolution*backingImage.height(), backingImage.width());
}

int SourceImage::getColumns() const
{
	if (backingImage.width() <= backingImage.height())
		return resolution;
	else
		return divide(resolution*backingImage.width(), backingImage.height());
}

uint64_t SourceImage::divide(uint64_t a, uint64_t b)
{
	return (a + b/2) / b;
}
