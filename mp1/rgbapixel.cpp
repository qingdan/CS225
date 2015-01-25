#include "rgbapixel.h"

RGBAPixel:: RGBAPixel(){
       
//your code
  red =  255;
  green = 255;
  blue = 255;
  alpha = 255;
}

RGBAPixel::RGBAPixel( uint8_t red,
        uint8_t green,
        uint8_t blue){
       //your code
  this->red = red;
  this->green = green;
  this->blue = blue;
     alpha = 255;
}
