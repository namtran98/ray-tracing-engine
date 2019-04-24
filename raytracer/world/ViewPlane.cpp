#include "ViewPlane.hpp"

// Constructor
ViewPlane::ViewPlane(){
  hres = 640;
  vres = 480;
  top_left = Point3D(-320,-240, 0);
  bottom_right = Point3D(-320+640, -240+480,0);
}  // default: 640 x 480 view plane at (-320, -240) with pixel size 1.

// Copy constructor and assignment operator.
ViewPlane::ViewPlane(const ViewPlane& other){
  hres = other.hres;
  vres = other.vres;
  top_left = other.top_left;
  bottom_right = other.bottom_right;
}

ViewPlane& ViewPlane::operator= (const ViewPlane& rhs){
  this->hres = rhs.hres;
  this->vres = rhs.vres;
  this->top_left = rhs.top_left;
  this->bottom_right = rhs.bottom_right;
  return *this;
}

// Destructor.
ViewPlane::~ViewPlane(){
}