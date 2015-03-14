/**
 * @file rgbapixel.h
 * Definition of the RGBAPixel class for the EasyPNG library.
 *
 * @author Chase Geigle
 * @date Spring 2012
 */
#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H

#include <cstdint>
#include <ostream>

using std::uint8_t;

/**
 * Represents a single pixel in an image.
 */
class RGBAPixel
{
	public:
		uint8_t red; /**< Byte for the red component of the pixel. */
		uint8_t green; /**< Byte for the green component of the pixel. */
		uint8_t blue; /**< Byte for the blue component of the pixel. */
		uint8_t alpha; /**< Byte for the alpha component of the pixel. */

        /** @cond POST_MP1 */

		/**
		 * Equality operator.
		 * @param other Other pixel to check equality with.
		 */
		bool operator==(RGBAPixel const & other) const;

		/**
		 * Inequality operator.
		 * @param other Other pixel to check inequality with.
		 */
		bool operator!=(RGBAPixel const & other) const;

		/**
		 * Less than operator. Provided to give some ordering notion to
		 * RGBAPixels.
		 * @param other Other pixel to compare with.
		 */
		bool operator<(RGBAPixel const & other) const;

        /** @endcond */

		/**
		 * Constructs a default RGBAPixel. A default pixel is completely
         * opaque (non-transparent) and white. Opaque implies that the
         * alpha component of the pixel is 255. Lower values are
         * transparent.
		 */
		RGBAPixel();

		/**
         * Constructs an opaque RGBAPixel with the given red, green, blue
         * color values. The alpha component of the pixel constructed
         * should be 255.
		 * @param red Red component for the new pixel.
		 * @param green Green component for the new pixel.
		 * @param blue Blue component for the new pixel.
		 */
		RGBAPixel(uint8_t red, uint8_t green, uint8_t blue);

        /** @cond POST_MP1 */

		/**
		 * Constructs an RGBAPixel with the given red, green, blue, and
		 * alpha components.
		 * @param red Red component for the new pixel.
		 * @param green Green component for the new pixel.
		 * @param blue Blue component for the new pixel.
		 * @param alpha Alpha component for the new pixel (controls
		 *	transparency).
		 */
		RGBAPixel(uint8_t red, uint8_t green, uint8_t blue,
				  uint8_t alpha);
        
        /** @endcond */

};

/** @cond POST_MP1 */

/**
 * Stream operator that allows pixels to be written to standard streams
 * (like cout).
 *
 * @param out Stream to write to.
 * @param pixel Pixel to write to the stream.
 */
std::ostream & operator<<(std::ostream & out, RGBAPixel const & pixel);

/** @endcond */

#endif // RGBAPIXEL_H
