#include "Plane.hpp"
#include <cmath>
// Constructors.
Plane::Plane(){
    a = Point3D(0,0,0);
    n = Vector3D(0,0,1);
    n.normalize();
    material_ptr = NULL;
}  // set plane to xz-plane.

Plane::Plane(const Point3D& pt, const Vector3D& normal){
    a = pt;
    n = normal;
    material_ptr = NULL;
}  // set a; n parallel to normal.

// Copy constructor and assignment operator.
Plane::Plane(const Plane& object){
    a = object.a;
    n = object.n;
    material_ptr = object.material_ptr;
}

Plane& Plane::operator=(const Plane& rhs){
    this->a = rhs.a;
    this->n = rhs.n;
    this->material_ptr = rhs.material_ptr;
    return *this;
}

// Destructor.
Plane::~Plane(){

}

// Virtual copy constructor.
Plane* Plane::clone() const{
    return new Plane(*this);
}

// Ray intersection. Set t and sinfo as per intersection with this object.
bool Plane::hit(const Ray& ray, float& t_min, ShadeInfo& s) const{
  const float EPSILON = .000001;
    // d * n
    double check = ray.d * n;
    if(std::abs(check) > 0.0){
        // calc and set info
        float t = ((a-ray.o) * n)/check;
        if (t > EPSILON){
          t_min = t;
          s.normal = n;
          s.hit_point = ray.o + t * ray.d;
          return true;
        }
    }
    return false;
}
