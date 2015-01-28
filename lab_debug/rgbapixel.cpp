/**
 * @file rgbapixel.cpp
 * Implementation of the RGBAPixel class for the EasyPNG library.
 *
 * @author Chase Geigle
 * @date Spring 2012
 */
#include "rgbapixel.h"

RGBAPixel::RGBAPixel() : red(255), green(255), blue(255), alpha(255)
{
	/* nothing */
}

RGBAPixel::RGBAPixel(uint8_t r, uint8_t g, uint8_t b)
	: red(r), green(g), blue(b), alpha(255)
{
	/* nothing */
}

RGBAPixel::RGBAPixel(uint8_t r, uint8_t g, uint8_t b,
		             uint8_t a) : red(r), green(g), blue(b), alpha(a)
{
	/* nothing */
}

bool RGBAPixel::operator==(RGBAPixel const & other) const
{
	return red == other.red && green == other.green && blue == other.blue &&
		alpha == other.alpha;
}

bool RGBAPixel::operator!=(RGBAPixel const & other) const
{
	return !(*this == other);
}

bool RGBAPixel::operator<(RGBAPixel const & other) const
{
	if (red != other.red)
		return red < other.red;
	if (green != other.green)
		return green < other.green;
	return blue < other.blue;
}

std::ostream & operator<<(std::ostream & out, RGBAPixel const & pixel)
{
	out << "(" << (int) pixel.red << "," << (int) pixel.green << ","
		<< (int) pixel.blue << ")";
	if (pixel.alpha != 255)
		out << " a:" << pixel.alpha;
	return out;
}
