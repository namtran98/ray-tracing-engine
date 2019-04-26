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
bool Plane::hit(const Ray& ray, float& t, ShadeInfo& s) const{
    // d * n
    double check = ray.d * n;
    if(std::abs(check) > 0.0){
        // calc and set info
        float calcedT = ((a-ray.o) * n)/check;
        t = calcedT;
        s.t = t;
        // not sure what depth is
        s.depth = 0;
        s.hit = true;
        // i believe this is it
        s.hit_point = ray.o + t * ray.d;
        // maybe
        s.material_ptr = material_ptr;
        s.normal = n;
        s.ray = ray;
        return true;
    }
    return false;
}
