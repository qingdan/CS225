/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 */

#ifndef COLOR_H_
#define COLOR_H_

#include "png.h"

namespace color { 

/* Format in initialization is blue, green, red, alpha */
const RGBAPixel WHITE(255, 255, 255);
const RGBAPixel BLACK(0, 0, 0);
const RGBAPixel GRAY(149, 145, 140);
const RGBAPixel RED(255, 0, 0);
const RGBAPixel ORANGE(255, 127, 0);
const RGBAPixel YELLOW(255, 255, 0);
const RGBAPixel GREEN(0, 255, 0);
const RGBAPixel TURQUOISE(0, 255, 255);
const RGBAPixel BLUE(0, 0, 255);
const RGBAPixel PURPLE(127, 0, 255);
const RGBAPixel PINK(251, 126, 253);

}  // namespace color

#endif  // COLOR_H_
