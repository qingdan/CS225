#ifndef IMAGE_H
#define IMAGE_H
#include <cstdint>
#include <iostream>
#include"png.h"
#include"rgbapixel.h"
using std::uint8_t;

//it is a subclass of png, but have more member funtions


class Image : public PNG
{    public:
    // the function definitions from the Doxygen go here

  Image(){};/*creates a default contructor*/
 void flipleft();
 void adjustbrightness (int r, int g, int b);
 void invertcolors ();
};


#endif
