/**
 * @file solidColorPicker.h
 * Definition of a solid color picker.
 *
 * @author CS 225 Staff
 * @date Fall 2010
 */
#ifndef SOLIDCOLORPICKER_H
#define SOLIDCOLORPICKER_H

#include "colorPicker.h"

/**
 * solidColorPicker: a functor that determines the color that should be
 * used given an x and y coordinate using a solid pattern. You can create
 * private helper functions inside this class, as well as local storage, if
 * necessary. Remember to overload a destructor if you need to.
 *
 * @author CS 225 Staff
 * @date Fall 2010
 */
class solidColorPicker : public colorPicker {
	public:
		/**
		 * Constructs a new solidColorPicker.
		 * 
		 * @param fillColor The color for this color picker.
		 */
		solidColorPicker( RGBAPixel fillColor );

		/**
		 * Picks the color for pixel (x, y).
		 *
		 * Simply returns the same color (used to construct the picker) all
		 * of the time.
		 */
		virtual RGBAPixel operator()( int x, int y );
	private:
		/**
		 * @todo Define any additional private member variables or helper
		 *	functions here as you see fit.
		 */
};

#endif
