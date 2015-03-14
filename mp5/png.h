/**
 * @file png.h
 * Definition of the PNG class for the EasyPNG library.
 * @see http://zarb.org/~gc/html/libpng.html
 *
 * @author Chase Geigle
 * @date Created: Spring 2012
 * @date Modified: Summer 2012
 * @date Modified by Sean Massung in Summer 2013, s/int/size_t
 */
#ifndef EPNG_H
#define EPNG_H

// c-style includes
#include <stdio.h>
#include <stdlib.h>
#include <png.h>

// c++ style includes
#include <string>
#include <iostream>
#include <sstream>

// local includes
#include "rgbapixel.h"

using std::cerr;
using std::endl;
using std::string;
using std::stringstream;

/**
 * Represents an entire png formatted image.
 */
class PNG
{
    public:
        /**
         * Creates a default PNG image (that is, a 1x1 opaque white image).
         */
        PNG();

        /**
         * Creates a default PNG image of the desired dimensions (that is,
         * a width x height opaque white image).
         * @param width Width of the new image.
         * @param height Height of the new image.
         */
        PNG(size_t width, size_t height);

        /**
         * Creates a PNG image by reading a file in from disk.
         * @param file_name Name of the file to be read in to the image.
         */
        PNG(string const & file_name);

        /**
         * Copy constructor: creates a new PNG image that is a copy of
         * another.
         * @param other PNG to be copied.
         */
        PNG(PNG const & other);

        /**
         * Destructor: frees all memory associated with a given PNG object.
         * Invoked by the system.
         */
        ~PNG();

        /**
         * Assignment operator for setting two PNGs equal to one another.
         * @param other Image to copy into the current image.
         * @return The current image for assignment chaining.
         */
        PNG const & operator=(PNG const & other);

        /**
         * Equality operator: checks if two images are the same.
         * @param other Image to be checked.
         * @return Whether the current image is equal to the other image.
         */
        bool operator==(PNG const & other) const;

        /**
         * Inequality operator: checks if two images are different.
         * @param other Image to be checked.
         * @return Whether the current image differs from the other image.
         */
        bool operator!=(PNG const & other) const;

        /**
         * Non-const pixel access operator. Gets a pointer to the pixel at
         * the given coordinates in the image. (0,0) is the upper left
         * corner. This pointer allows the image to be changed.
         * @param x X-coordinate for the pixel pointer to be grabbed from.
         * @param y Y-coordinate for the pixel pointer to be grabbed from.
         * @return A pointer to the pixel at the given coordinates.
         */
        RGBAPixel * operator()(size_t x, size_t y);

        /**
         * Const pixel access operator. Const version of the previous
         * operator(). Does not allow the image to be changed via the
         * pointer.
         * @param x X-coordinate for the pixel pointer to be grabbed from.
         * @param y Y-cooridnate for the pixel pointer to be grabbed from.
         * @return A pointer to the pixel at the given coordinates (can't
         *	change the pixel through this pointer).
         */
        RGBAPixel const * operator()(size_t x, size_t y) const;

        /**
         * Reads in a PNG image from a file.
         * Overwrites any current image content in the PNG. In the event of
         * failure, the image's contents are undefined.
         * @param file_name Name of the file to be read from.
         * @return Whether the image was successfully read in or not.
         */
        bool readFromFile(string const & file_name);

        /**
         * Writes a PNG image to a file.
         * @param file_name Name of the file to write to.
         * @return Whether the file was written successfully or not.
         */
        bool writeToFile(string const & file_name);

        /**
         * Gets the width of this image.
         * @return Width of the image.
         */
        size_t width() const;

        /**
         * Gets the height of this image.
         * @return Height of the image.
         */
        size_t height() const;

        /**
         * Resizes the image to the given coordinates. Attempts to preserve
         * existing pixel data in the image when doing so, but will crop if
         * necessary. No pixel interpolation is done.
         * @param width New width of the image.
         * @param height New height of the image.
         */
        void resize(size_t width, size_t height);

    private:
        // storage
        size_t _width;
        size_t _height;
        RGBAPixel * _pixels;

        // private helper functions
        bool _read_file(string const & file_name);
        void _clear();
        void _copy(PNG const & other);
        void _blank();
        void _init();
        void _min_clamp_x(size_t & width) const;
        void _min_clamp_y(size_t & height) const;
        void _min_clamp_xy(size_t & width, size_t & height) const;
        void _clamp_xy(size_t & width, size_t & height) const;
        bool _pixels_same(const RGBAPixel & first, const RGBAPixel & second) const;
        RGBAPixel & _pixel(size_t x, size_t y) const;
};

#endif // EPNG_H
