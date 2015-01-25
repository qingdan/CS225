#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H

#include <cstdint>
#include <ostream>
using std::uint8_t;

class RGBAPixel{
public:
      uint8_t red;
      uint8_t green;
      uint8_t blue;
      uint8_t alpha;

     RGBAPixel();
     RGBAPixel(
               uint8_t red,
               uint8_t green,
               uint8_t blue);
};
#endif

