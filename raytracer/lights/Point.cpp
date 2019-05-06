#include "Point.hpp"

Point::Point(): Light(), ls(1), pos(0) {}
Point::Point(float c, float _ls, Point3D _pos) : Light(c), ls(_ls), pos(_pos) {}
Point::Point(float r, float g, float b, float _ls, Point3D _pos) : Light(r,g,b), ls(_ls), pos(_pos) {}
Point::Point(const RGBColor& _color, float _ls, Point3D _pos) : Light(_color), ls(_ls), pos(_pos) {}
Point::~Point(){}

Point::Point(const Point& rhs){
  color = rhs.color;
  ls = rhs.ls;
  pos = rhs.pos;
}
Point& Point::operator= (const Point& rhs){
  color = rhs.color;
  ls = rhs.ls;
  pos = rhs.pos;
  return *this;
}


// Normalized direction vector from light source to hit point.
Vector3D Point::get_direction(const ShadeInfo& sinfo) const{
  Vector3D dir = pos - sinfo.hit_point;
  dir.normalize();
  return dir;
}

// Luminance from this light source at hit point.
RGBColor Point::L(const ShadeInfo& sinfo) const{
  return ls * color;
}

Point* Point::clone() const{
  return new Point(*this);
}
