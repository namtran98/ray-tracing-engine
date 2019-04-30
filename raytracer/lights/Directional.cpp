#include "Directional.hpp"

Directional::Directional(): Light(), ls(1), dir(0, 0, -1) {
  dir.normalize();
}
Directional::Directional(float c, float _ls, Vector3D _dir) : Light(c), ls(_ls), dir(_dir) {
  dir.normalize();
}
Directional::Directional(float r, float g, float b, float _ls, Vector3D _dir) : Light(r,g,b), ls(_ls), dir(_dir) {
  dir.normalize();
}
Directional::Directional(const RGBColor& _color, float _ls, Vector3D _dir) : Light(_color), ls(_ls), dir(_dir) {
  dir.normalize();
}
Directional::~Directional(){}

Directional::Directional(const Directional& rhs){
  color = rhs.color;
  ls = rhs.ls;
  dir = rhs.dir;
}
Directional& Directional::operator= (const Directional& rhs){
  color = rhs.color;
  ls = rhs.ls;
  dir = rhs.dir;
  return *this;
}


// Normalized direction vector from light source to hit directional.
Vector3D Directional::get_direction(ShadeInfo& sinfo) const{
  return dir;
}

// Luminance from this light source at hit directional.
RGBColor Directional::L(ShadeInfo& sinfo) const{
  return ls * color;
}

Directional* Directional::clone() const{
  return new Directional(*this);
}
