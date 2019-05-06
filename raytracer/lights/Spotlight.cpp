#include "Spotlight.hpp"
Spotlight::Spotlight(): Point(), dir(0, -1, 0), theta(1) {}
Spotlight::Spotlight(float c, float ls, Point3D _pos, Vector3D _dir, float _theta) : Point(c, ls, _pos), dir(_dir), theta(_theta) {}
Spotlight::Spotlight(float r, float g, float b, float ls, Point3D _pos, Vector3D _dir, float _theta): Point(r, g, b, ls, _pos), dir(_dir), theta(_theta) {}
Spotlight::Spotlight(const RGBColor& _color, float ls, Point3D _pos, Vector3D _dir, float _theta) : Point(_color, ls, _pos), dir(_dir), theta(_theta) {}
Spotlight::~Spotlight(){}

// Copy constructor and assignment operator.
Spotlight::Spotlight(const Spotlight& rhs): Point(rhs.color, rhs.ls, rhs.pos), dir(rhs.dir), theta(rhs.theta){}
Spotlight& Spotlight::operator= (const Spotlight& rhs){
  color = rhs.color;
  ls = rhs.ls;
  pos = rhs.pos;
  dir = rhs.dir;
  theta = rhs.theta;
  return *this;
}

Spotlight* Spotlight::clone() const{
  return new Spotlight(*this);
}

void Spotlight::set_theta(float t){
  theta = t;
}

void Spotlight::set_direction(float c){
  dir = Vector3D(c);
  dir.normalize();
}
void Spotlight::set_direction(float x, float y, float z){
  dir = Vector3D(x, y, z);
  dir.normalize();
}
void Spotlight::set_direction(const Vector3D& d){
  dir = d;
  dir.normalize();
}

Vector3D Spotlight::get_direction(const ShadeInfo& sinfo) const{
  // TODO: Figure out if this should be like a directional
  // light or a point light or something else
  Vector3D to_pt = pos - sinfo.hit_point;
  to_pt.normalize();
  return to_pt;
}

// Luminance from this light source at hit point.
RGBColor Spotlight::L(const ShadeInfo& sinfo) const{
  return ls * color;
}

