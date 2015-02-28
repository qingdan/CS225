#include "rainbowColorPicker.h"
#include <math.h>

using std::pair;
using std::map;

rainbowColorPicker::rainbowColorPicker(long double freq_)
	: iter(0), freq(freq_) {
	
}

RGBAPixel rainbowColorPicker::operator()(int x, int y) {
	PNGmap::iterator stored = prev.find(pair<int,int>(x, y));
	if (stored == prev.end())
	{
		RGBAPixel next = nextColor();
		prev[pair<int,int>(x, y)] = next;
		return next;
	}
	else
		return stored->second;
}

// http://www.krazydad.com/makecolors.php
RGBAPixel rainbowColorPicker::nextColor() {
	RGBAPixel ret;
	ret.red   = (uint8_t)(sin(freq*iter + 0) * 127 + 128);
	ret.green = (uint8_t)(sin(freq*iter + 2) * 127 + 128);
	ret.blue  = (uint8_t)(sin(freq*iter + 4) * 127 + 128);
	iter++;
	return ret;
}
