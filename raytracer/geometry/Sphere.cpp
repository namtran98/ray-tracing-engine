#include "Sphere.hpp"
#include "../utilities/Constants.hpp"
#include <cmath>

Sphere::Sphere(): c(0), r(0){}
Sphere::Sphere(const Point3D& center, float radius) : c(center), r(radius){}
Sphere::Sphere(const Sphere& object){
  r = object.r;
  c = object.c;
}

Sphere& Sphere::operator=(const Sphere& rhs){
  r = rhs.r;
  c = rhs.c;
  return *this;
}

Sphere::~Sphere(){}

bool Sphere::hit(const Ray& ray, float& t_min, ShadeInfo& s) const{
  float t;
  Vector3D origin_to_center = ray.o - c;
  double a = ray.d * ray.d;
  double b = 2.0 * origin_to_center * ray.d;
  double c = (origin_to_center * origin_to_center) - (r * r);
  double discrim = (b * b) - 4.0 * a * c;
  if (discrim < 0.0){
    return false;
  } else {
    double e = sqrt(discrim);
    double denom = 2.0 * a;
    t = (-b - e) / denom; // Try smaller root first
    if (t > kEpsilon){
      t_min = t;
      s.normal = (origin_to_center + t * ray.d) / r;
      s.hit_point = ray.o + t * ray.d;
      s.hit = true;
      s.material_ptr = material_ptr;
      return true;
    }

    t = (-b + e); // Else try larger root
    if (t > kEpsilon){
      t_min = t;
      s.normal = (origin_to_center + t * ray.d) / r;
      s.hit_point = ray.o + t * ray.d;
      s.hit = true;
      s.material_ptr = material_ptr;
      return true;
    }
  }
  return false;
}

Sphere* Sphere::clone() const{
  return new Sphere(*this);
}
