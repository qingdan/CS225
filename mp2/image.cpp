#include "image.h"


void Image::flipleft()
{
    
      RGBAPixel *temp;
      temp = new RGBAPixel;
    int  theheight = this->height();
     int thewidth = this->width();
      for (int y = 0; y < theheight; y++)
	{
           for (int x = 0; x <= (thewidth - 1)/2; x++)
           { 
                *temp = *(*this)(x,y);
		*(*this)(x,y) = *(*this)(thewidth - x -1,y);
		*(*this)(thewidth - x -1,y) = *temp;
            }
	 }

      delete temp; 

}

 void Image::adjustbrightness (int r, int g, int b)
 {   int theheight = this->height();
     int thewidth = this->width();
   for (int y = 0; y < theheight; y++)
	  {
           for(int x = 0; x < thewidth; x++)
	     {
               if ((*this)(x,y)->red + r > 255)
               (*this)(x,y)->red = 255;
               else if((*this)(x,y)->red + r < 0)
               (*this)(x,y)->red = 0;
               else (*this)(x,y)->red += r;
               if ((*this)(x,y)->green + g > 255)
               (*this)(x,y)->green = 255;
               else if((*this)(x,y)->green + g < 0)
               (*this)(x,y)->green = 0;
               else (*this)(x,y)->green += g;
               if ((*this)(x,y)->blue + b > 255)
               (*this)(x,y)->blue = 255;
               else if((*this)(x,y)->blue + b < 0)
               (*this)(x,y)->blue = 0;
               else (*this)(x,y)->blue += b;

            }

          }
	
}

 void Image::invertcolors()
 {     int theheight = this->height();
     int thewidth = this->width();
   for (int y = 0; y < theheight; y++)
	  {
           for(int x = 0; x < thewidth; x++)
	     {  
         (*this)(x,y)->red = 255 - (*this)(x,y)->red;    
         (*this)(x,y)->green = 255 - (*this)(x,y)->green;
         (*this)(x,y)->blue = 255 - (*this)(x,y)->blue; 
             }
	  }
 }
