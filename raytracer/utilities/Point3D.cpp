#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <cmath>

Point3D::Point3D() : x(0), y(0), z(0) {}
Point3D::Point3D(const float c) : x(c), y(c), z(c){}
Point3D::Point3D(const float _x, const float _y,
                 const float _z) : x(_x), y(_y), z(_z) {}
Point3D::~Point3D(){}

Point3D::Point3D(const Point3D& p){
  x = p.x;
  y = p.y;
  z = p.z;
}

Point3D& Point3D::operator= (const Point3D& p){
  x = p.x;
  y = p.y;
  z = p.z;
  return *this;
}

Point3D Point3D::operator- (void) const {
  Point3D ret_val(-1 * x, -1 * y, -1 * z);
  return ret_val;
}

// Point A - Point B gives the vector from B to A
Vector3D Point3D::operator- (const Point3D& p) const{ // vector joining two points
  Vector3D ret_val(x - p.x, y - p.y, z - p.z);
  return ret_val;
}

Point3D Point3D::operator+ (const Vector3D& v) const { // addition of a vector
  Point3D ret_val(x + v.x, y + v.y, z + v.z);
  return ret_val;
}

Point3D Point3D::operator- (const Vector3D& v) const { // addition of a vector
  Point3D ret_val(x - v.x, y - v.y, z - v.z);
  return ret_val;
}

Point3D Point3D::operator* (const float s) const { // scale the point by a factor, s.
  Point3D ret_val(x * s, y * s, z * s);
  return ret_val;
}

float Point3D::d_squared(const Point3D& p) const { // square of distance
  return std::pow(x - p.x, 2) + std::pow(y - p.y, 2) + std::pow(z - p.z, 2);
}

float Point3D::distance(const Point3D& p) const { // square of distance
  return std::pow(d_squared(p), .5);
}

Point3D operator* (const float a, const Point3D& pt) { // Scale pt by a factor, s.
  Point3D ret_val(pt);
  return ret_val * a;
}
