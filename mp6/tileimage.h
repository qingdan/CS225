/**
 * @file tileimage.h
 * Definition of the TileImage class.
 */

#ifndef TILEIMAGE_H
#define TILEIMAGE_H

#include <math.h>
#include <stdint.h>
#include "png.h"

/**
 * Represents a Tile in the Photomosaic.
 */
class TileImage
{
	private:
	PNG image;
	RGBAPixel averageColor;

	public:
	TileImage();
	explicit TileImage(const PNG & theImage);
	RGBAPixel getAverageColor() const { return averageColor; }
	int getResolution() const { return image.width(); }
	void paste(PNG & canvas, int startX, int startY, int resolution) const;
	
	private:
	static PNG cropSourceImage(const PNG & source);
	RGBAPixel calculateAverageColor() const;
	RGBAPixel getScaledPixelDouble(double startX, double endX, double startY, double endY) const;
	RGBAPixel getScaledPixelInt(int startX, int endX, int startY, int endY) const;
	static uint64_t divide(uint64_t a, uint64_t b) { return (a + b/2) / b; }
	static int divide(int a, int b) { return divide(static_cast<uint64_t>(a), static_cast<uint64_t>(b)); }
	static int fdivide(double a, double b) { return a / b + 0.5; }
	static double frac(double x) { return x - floor(x); }
};

#endif // TILEIMAGE_H
