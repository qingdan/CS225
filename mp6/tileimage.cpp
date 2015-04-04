#include <algorithm>
#include "tileimage.h"

using namespace std;

TileImage::TileImage()
	: image(1, 1)
{
	averageColor = *image(0, 0);
}

TileImage::TileImage(const PNG & source)
	: image(cropSourceImage(source))
{
	averageColor = calculateAverageColor();
}

PNG TileImage::cropSourceImage(const PNG & source)
{
	int height = source.height();
	int width  = source.width();
	int resolution = min(width, height);
	
	int startX = 0;
	int startY = 0;

	if (width != height)
	{
		if (height > width)
			startY = (height - width) / 2;
		else
			startX = (width - width) / 2;
	}

	PNG cropped(resolution, resolution);

	for (int y = 0; y < resolution; y++)
		for (int x = 0; x < resolution; x++)
			*cropped(x, y) = *source(startX + x, startY + y);

	return cropped;
}

RGBAPixel TileImage::calculateAverageColor() const
{
	uint64_t r = 0;
	uint64_t g = 0;
	uint64_t b = 0;

	for (size_t y = 0; y < image.height(); y++)
	{
		for (size_t x = 0; x < image.width(); x++)
		{
			r += image(x, y)->red;
			g += image(x, y)->green;
			b += image(x, y)->blue;
		}
	}

	RGBAPixel color;
	uint64_t numPixels = image.width() * image.height();
	color.red   = divide(r, numPixels);
	color.green = divide(g, numPixels);
	color.blue  = divide(b, numPixels);
	return color;
}

void TileImage::paste(PNG & canvas, int startX, int startY, int resolution) const
{
	// If possible, avoid floating point comparisons. This helps ensure that students'
	// photomosaic's are diff-able with solutions
	if (getResolution() % resolution == 0)
	{
		int scalingRatio = getResolution() / resolution;
		
		for (int x = 0; x < resolution; x++)
		{
			for (int y = 0; y < resolution; y++)
			{
				int pixelStartX = (x)   * scalingRatio;
				int pixelEndX   = (x+1) * scalingRatio;
				int pixelStartY = (y)   * scalingRatio;
				int pixelEndY   = (y+1) * scalingRatio;
				
				*canvas(startX + x, startY + y) = getScaledPixelInt(pixelStartX, pixelEndX, pixelStartY, pixelEndY);
			}
		}
	}
	else // scaling is necessary
	{
		double scalingRatio = static_cast<double>(getResolution()) / resolution;

		for (int x = 0; x < resolution; x++)
		{
			for (int y = 0; y < resolution; y++)
			{
				double pixelStartX = (double)(x)   * scalingRatio;
				double pixelEndX   = (double)(x+1) * scalingRatio;
				double pixelStartY = (double)(y)   * scalingRatio;
				double pixelEndY   = (double)(y+1) * scalingRatio;
				
				*canvas(startX + x, startY + y) = getScaledPixelDouble(pixelStartX, pixelEndX, pixelStartY, pixelEndY);
			}
		}
	}
}

RGBAPixel TileImage::getScaledPixelDouble(double startX, double endX, double startY, double endY) const
{
	double leftFrac   = 1.0 - frac(startX);
	double rightFrac  = frac(endX);
	double topFrac    = 1.0 - frac(startX);
	double bottomFrac = frac(endX);

	int startXint = static_cast<int>(startX);
	int endXint   = static_cast<int>(ceil(endX));
	int startYint = static_cast<int>(startY);
	int endYint   = static_cast<int>(ceil(endY));

	double r = 0.0;
	double g = 0.0;
	double b = 0.0;
	double totalPixels = 0.0;

	for (int x = startXint; x < endXint; x++)
	{
		for (int y = startYint; y < endYint; y++)
		{
			double weight = 1.0;
			if (x == startXint) weight *= leftFrac;
			if (x == endXint)   weight *= rightFrac;
			if (y == startYint) weight *= topFrac;
			if (y == endYint)   weight *= bottomFrac;

			r += image(x, y)->red   * weight;
			g += image(x, y)->green * weight;
			b += image(x, y)->blue  * weight;
			totalPixels += weight;
		}
	}

	RGBAPixel avg;
	avg.red   = fdivide(r, totalPixels);
	avg.green = fdivide(g, totalPixels);
	avg.blue  = fdivide(b, totalPixels);
	return avg;
}

RGBAPixel TileImage::getScaledPixelInt(int startXint, int endXint, int startYint, int endYint) const
{
	uint64_t r = 0;
	uint64_t g = 0;
	uint64_t b = 0;
	uint64_t totalPixels = 0;

	for (int x = startXint; x < endXint; x++)
	{
		for (int y = startYint; y < endYint; y++)
		{
			r += image(x, y)->red;
			g += image(x, y)->green;
			b += image(x, y)->blue;
			totalPixels++;
		}
	}

	RGBAPixel avg;
	avg.red   = divide(r, totalPixels);
	avg.green = divide(g, totalPixels);
	avg.blue  = divide(b, totalPixels);
	return avg;
}
