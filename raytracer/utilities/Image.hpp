#pragma once
#include <string>

/**
   This file declares the Image class which is a utility for storing image
   pixels and writing them to file in PPM format.

   x increases to the right, and y to the bottom.
*/

// Forward Declarations
class RGBColor;
class ViewPlane;

class Image {
private:
  RGBColor **colors;  // pixel colors.
  int pic_hres;
  int pic_vres;

public:
  // Constructors.
  Image(int hres, int vres);  // initialize blank image of given size.
  Image(const ViewPlane& vplane);  // initialize blank image of same size as vplane.

  // Destructor.
  ~Image();  // free memory.

  // Set pixel color.
  void set_pixel(int x, int y, RGBColor color);

  // Write image to file in PPM format.
  void write_ppm(std::string path);
};
