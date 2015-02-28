#include "solidColorPicker.h"

/**
 * Constructs a new solidColorPicker.
 * 
 * @param fillColor The color for this color picker.
 */
solidColorPicker::solidColorPicker(RGBAPixel fillColor)
{
	/**
	 * @todo Initialize a new solidColorPicker here!
	 */
}

/**
 * Picks the color for pixel (x, y).
 *
 * Simply returns the same color (used to construct the picker) all of the
 * time.
 */
RGBAPixel solidColorPicker::operator()(int x, int y)
{
	/**
	 * @todo Return the appropriate color here! You will have to replace
	 *	the following line.
	 */
	return RGBAPixel();
}
