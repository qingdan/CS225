/**
 * @file gradientColorPicker.h
 * Definition of a gradient color picker.
 *
 * @author CS 225 Staff
 * @date Fall 2010
 */
#ifndef GRADIENTCOLORPICKER_H
#define GRADIENTCOLORPICKER_H

#include "colorPicker.h"
#include <math.h>
#include <iostream>

/**
 * gradientColorPicker: a functor that determines the color that should be
 * used given an x and y coordinate using a gradient strategy. You can
 * create private helper functions inside this class, as well as local
 * storage, if necessary. Remember to overload a destructor if you need to.
 *
 * @author CS 225 Staff
 * @date Fall 2010
 */
class gradientColorPicker : public colorPicker {
	public:
		/**
		 * Constructs a new gradientColorPicker.
		 *
		 * @param fadeColor1 The first color to start the gradient at.
		 * @param fadeColor2 The second color to end the gradient with.
		 * @param radius How quickly to transition to fadeColor2.
		 * @param centerX X coordinate for the center of the gradient.
		 * @param centerY Y coordinate for the center of the gradient.
		 */
		gradientColorPicker( RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, int centerX, int centerY );

		/**
		 * Picks the color for pixel (x, y).
		 *
		 * The first color fades into the second color as you move from the
		 * initial fill point, the center, to the radius. Beyond the
		 * radius, all pixels should be just color2. 
		 *
		 * You should calculate the distance between two points using the
		 * standard Manhattan distance formula, 
		 * 
         * \f$d = |center\_x - given\_x| + |center\_y - given\_y|\f$
		 *
		 * Then, scale each of the three channels (R, G, and B) from
		 * fadeColor1 to fadeColor2 linearly from d = 0 to d = radius. 
		 *
		 * For example, the red color at distance d where d is less than
		 * the radius must be
         *
         * \f$ redFill = fadeColor1.red - \left\lfloor
           \frac{d*fadeColor1.red}{radius}\right\rfloor +
           \left\lfloor\frac{d*fadeColor2.red}{radius}\right\rfloor\f$
		 *
		 * Note that all values are integers. If you do not follow this
		 * formula, your colors may be very close but round differently
		 * than ours.
		 *
		 * @param x The x coordinate to pick a color for.
		 * @param y The y coordinate to pick a color for.
		 * @return The color selected for (x, y).
		 */
		virtual RGBAPixel operator()( int x, int y );

	private:
		/** 
		 * @todo Add any necessary private storage here! You may also add
		 *	private helper functions as you see fit.
		 */
};

#endif
