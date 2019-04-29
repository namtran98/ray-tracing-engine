#include "Ray.hpp"

Ray::Ray(){
    o = Point3D(0,0,0);
    d = Vector3D(0,0,0);
    w = 1.0f;
}  // set origin and dir to (0, 0, 0), w to 1.

Ray::Ray(const Point3D& origin, const Vector3D& dir){
    o = origin;
    d = dir;
    w = 1.0f;
}  // set origin, dir; w is 1.

  // Copy constructor and assignment operator.
Ray::Ray(const Ray& ray){
    o = ray.o;
    d = ray.d;
    w = ray.w;
}

Ray& Ray::operator= (const Ray& rhs){
    this->o = rhs.o;
    this->d = rhs.d;
    this->w = rhs.w;
    return *this;
}

  // Destructor.
Ray::~Ray(void){
}
