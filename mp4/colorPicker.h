/**
 * @file colorPicker.h
 * 
 * Definition of a color picker abstract base class.
 *
 * @author CS 225 Staff
 * @date Fall 2010
 */
#ifndef COLORPICKER_H
#define COLORPICKER_H

#include "png.h"

/**
 * colorPicker: a functor that determines the color that should be used
 * given an x and y coordinate.
 *
 * @author CS 225 Staff
 * @date Fall 2010
 */
class colorPicker {
	public:
		/**
		 * Destructor: does nothing, but as it is virtual, you may overload
		 * it in derived classes if needed.
		 */
		virtual ~colorPicker() {};

		/**
		 * Picks the color for pixel (x, y).
		 *
		 * This function **must** be defined in the subclass! It chooses
		 * a color for the given point (x,y) and returns it.
		 *
		 * For example, the gridColorPicker::operator()() function is defined
		 * so as to return a color if x or y is divisible by the grid
		 * spacing, and white otherwise. In this way, if you colored each
		 * pixel in an image whatever color the gridColorPicker chose, you
		 * would end up with a grid.
		 *
		 * For the other patterns, you will have to figure out how to
		 * "pick" the colors.
		 *
		 * @param x The x coordinate of the pixel we want to pick a color
		 *	for.
		 * @param y The y coordinate of the pixel we want to pick a color
		 *	for.
		 * @return The color that the pixel at (x, y) should be.
		 */
		virtual RGBAPixel operator()(int x, int y) = 0;
};

#endif
