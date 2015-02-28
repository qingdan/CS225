#ifndef RAINBOWCOLORPICKER_H
#define RAINBOWCOLORPICKER_H

#include <stdint.h>
#include <map>
#include <utility>
#include "colorPicker.h"

class rainbowColorPicker : public colorPicker{
  public:
    rainbowColorPicker(long double freq_);
    virtual RGBAPixel operator()(int x, int y);

  private:
    RGBAPixel nextColor();

    typedef std::map<std::pair<int, int>, RGBAPixel> PNGmap;
    size_t iter;
    PNGmap prev;
	long double freq;
};

#endif
