#include "Ambient.hpp"
#include <iostream>

Ambient::Ambient(): Light(), ls(0) {}
Ambient::Ambient(float c, float _ls) : Light(c), ls(_ls) {}
Ambient::Ambient(float r, float g, float b, float _ls) : Light(r,g,b), ls(_ls) {}
Ambient::Ambient(const RGBColor& _color, float _ls) : Light(_color), ls(_ls) {}
Ambient::~Ambient(){}

Ambient::Ambient(const Ambient& rhs){
  color = rhs.color;
  ls = rhs.ls;
}
Ambient& Ambient::operator= (const Ambient& rhs){
  color = rhs.color;
  ls = rhs.ls;
  return *this;
}


// Normalized direction vector from light source to hit point.
// 0 vector from the textbook
Vector3D Ambient::get_direction(ShadeInfo& sinfo) const{
  std::cout << "Warning: Calling get direction on ambient light" << std::endl;
  return Vector3D(0);
}

// Luminance from this light source at hit point.
RGBColor Ambient::L(ShadeInfo& sinfo) const{
  return ls * color;
}

Ambient* Ambient::clone() const{
  return new Ambient(*this);
}
