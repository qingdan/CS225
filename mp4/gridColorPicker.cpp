#include "gridColorPicker.h"

gridColorPicker::gridColorPicker( RGBAPixel gridColor, int gridSpacing ) {
  color = gridColor;
  spacing = gridSpacing;
}

RGBAPixel gridColorPicker::operator()( int x, int y ) {
	if( x % spacing == 0 || y % spacing == 0 ){
		return color;
	} else {
		RGBAPixel ret;
		ret.red = ret.blue = ret.green = ret.alpha  = 255;
		return ret;
	}
}
