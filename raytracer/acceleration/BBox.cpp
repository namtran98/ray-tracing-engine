#include "BBox.hpp"
#include "../utilities/Constants.hpp"

BBox::BBox(): min_point(0), max_point(0) {}
BBox::BBox(Point3D min, Point3D max): min_point(min), max_point(max) {}
BBox::BBox(const BBox& v) : min_point(v.min_point), max_point(v.max_point) {}
BBox::~BBox(){}
BBox& BBox::operator= (const BBox& rhs){
  min_point = rhs.min_point;
  max_point = rhs.max_point;
  return *this;
}

bool BBox::hit(const Ray &ray) const{
  double ox = ray.o.x;
  double oy = ray.o.y;
  double oz = ray.o.z;
  double dx = ray.d.x;
  double dy = ray.d.y;
  double dz = ray.d.z;

  double tx_min, ty_min, tz_min;
  double tx_max, ty_max, tz_max;

  double a = 1.0 / dx;
  if (a >= 0){
    tx_min = (min_point.x - ox) * a;
    tx_max = (max_point.x - ox) * a;
  } else {
    tx_min = (max_point.x - ox) * a;
    tx_max = (min_point.x - ox) * a;
  }

  double b = 1.0 / dy;
  if (b >= 0){
    ty_min = (min_point.y - oy) * b;
    ty_max = (max_point.y - oy) * b;
  } else {
    ty_min = (max_point.y - oy) * b;
    ty_max = (min_point.y - oy) * b;
  }

  double c = 1.0 / dz;
  if (c >= 0){
    tz_min = (min_point.z - oz) * c;
    tz_max = (max_point.z - oz) * c;
  } else {
    tz_min = (max_point.z - oz) * c;
    tz_max = (min_point.z - oz) * c;
  }

  double t0, t1;
  // find largest entering t value
  if (tx_min > ty_min){
    t0 = tx_min;
  } else {
    t0 = ty_min;
  }
  if (tz_min > t0){
    t0 = tz_min;
  }

  // find smallest exiting t value
  if (tx_max < ty_max){
    t1 = tx_max;
  } else {
    t1 = ty_max;
  }
  if (tz_max < t1){
    t1 = tz_max;
  }

  return (t0 < t1 && t1 > kEpsilon);
}
