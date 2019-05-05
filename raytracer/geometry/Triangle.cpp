#include "Triangle.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Constants.hpp"

Triangle::Triangle() : a(0), b(0), c(0) {
  bbox = get_bounding_box();
}
Triangle::Triangle(const Point3D& _a,
                   const Point3D& _b, const Point3D& _c): a(_a), b(_b), c(_c){
                     bbox = get_bounding_box();
                   }

Triangle::Triangle(const Triangle& object){
  a = object.a;
  b = object.b;
  c = object.c;
  bbox = get_bounding_box();
}

Triangle& Triangle::operator=(const Triangle& rhs){
  a = rhs.a;
  b = rhs.b;
  c = rhs.c;
  bbox = rhs.bbox;
  return *this;
}

Triangle::~Triangle(){}


BBox Triangle::get_bounding_box(){
  double delta = 0.0001;

  Point3D min = Point3D(std::min(std::min(a.x, b.x), c.x) - delta, std::min(std::min(a.y, b.y), c.y) - delta, std::min(std::min(a.z, b.z), c.z) - delta);
  Point3D max = Point3D(std::max(std::max(a.x, b.x), c.x) + delta, std::max(std::max(a.y, b.y), c.y) + delta, std::max(std::max(a.z, b.z), c.z) + delta);

	return BBox(min, max);
}


// Using Moller Trumbore intersection algorithm as described here:
// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
bool Triangle::hit(const Ray& ray, float& t_min, ShadeInfo& si) const{
  Vector3D edge1, edge2, h, s, q;
  float _a, f, u, v;
  edge1 = b-a;
  edge2 = c-a;
  h = ray.d ^ edge2;
  _a = edge1 * h;
  if (_a > -kEpsilon && _a < kEpsilon){
    return false; // ray parallel to triangle
  }
  f = 1.0 / _a;
  s = ray.o - a;
  u = f * (s * h);
  if (u < 0.0 || u > 1.0){
    return false;
  }
  q = s ^ edge1;
  v = f * (ray.d * q);
  if (v < 0.0 || u + v > 1.0){
    return false;
  }
  float t = f * (edge2 * q);
  if (t > kEpsilon){
    si.hit_point = ray.o + (ray.d * t);
    si.normal = edge1 ^ edge2;
    si.hit = true;
    si.material_ptr = material_ptr;
    si.ray = ray;
    t_min = t;
    si.t = t;
    return true;
  } else {
    return false; // Line intersects but before the origin
  }

}

Triangle* Triangle::clone() const{
  return new Triangle(*this);
}
