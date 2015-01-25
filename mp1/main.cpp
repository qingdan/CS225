/*this is the main function
 *it uses the functions from the EasyPNG library to open a bitmap image named .png,
 *rotate the image by 180 degrees, and write the resulting image to the file out.png 
 */
#include <iostream>

#include "rgbapixel.h"
#include "png.h"
using namespace std;
 PNG rotate(PNG original, PNG result)
{ //this function rotate the original file 180 degree and return the result
  size_t height = original.height();
  size_t width = original.width();
  for (size_t yi = 0; yi < height; yi++)
    {
        for (size_t xi = 0; xi < width; xi++)
        {   result(width-xi-1,height-yi-1)->red = original(xi,yi)->red;
            result(width-xi-1,height-yi-1)->green = original(xi,yi)->green;
            result(width-xi-1,height-yi-1)->blue = original(xi,yi)->blue;
            result(width-xi-1,height-yi-1)->alpha = original(xi,yi)->alpha;
         }
     }
    return result;
}

int main()
{
    // Open a new PNG image from the file in.png.
    PNG image("in.png");

    // call the rotate function to rotate the image
    image =rotate(image, image);

    // output the file to output.png
    image.writeToFile("out.png"); 

    return 0;
}
