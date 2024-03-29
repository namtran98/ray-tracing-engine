#include "Image.hpp"
#include "RGBColor.hpp"
#include "../world/ViewPlane.hpp"

#include <fstream>

// NOTE: To get point (x,y), need to index by x then y

// initialize blank image of given size.
Image::Image(int hres, int vres){
  colors = new RGBColor *[hres];
  for(int i = 0; i < hres; i++){
    colors[i] = new RGBColor[vres];
  }
  pic_hres = hres;
  pic_vres = vres;
}

// initialize blank image of same size as vplane.
Image::Image(const ViewPlane& vplane){
  int hres = vplane.hres;
  int vres = vplane.vres;
  colors = new RGBColor *[hres];
  for(int i = 0; i < hres; i++){
    colors[i] = new RGBColor[vres];
  }
  pic_hres = hres;
  pic_vres = vres;
}

Image::~Image(){
  for(int i = 0; i < pic_hres; i++){
    delete[] colors[i];
  }
  delete[] colors;
}

// Set pixel color.
void Image::set_pixel(int x, int y, RGBColor color){
  colors[x][y] = color;
}

// NOTE: based on PPM reference found here:
// http://netpbm.sourceforge.net/doc/ppm.html

// Write image to file in PPM format.
void Image::write_ppm(std::string path){
  std::ofstream file;
  file.open(path);
  file << "P3\n";
  file << pic_hres << "\t";
  file << pic_vres << "\n";
  file << "255" << "\n"; // Max value
  // TODO: Figure out if this should be PPM of PPM plain and actually write
  // the pixel values
  for (int i = pic_vres; i >=0 ; i--){
    for (int j = 0; j < pic_hres; j++){
      file << (unsigned int) (255 * colors[j][i].r) << " ";
      file << (unsigned int) (255 * colors[j][i].g) << " ";
      file << (unsigned int) (255 * colors[j][i].b) << "\t";
    }
    file << "\n";
  }
  file.close();
}
