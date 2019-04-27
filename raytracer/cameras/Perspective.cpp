#include "Perspective.hpp"

// Constructors.
Perspective::Perspective(){
    pos = Point3D(0,0,0);
}  // set pos to origin.
Perspective::Perspective(float c){
    pos = Point3D(c,c,c);
}  // set pos to (c, c, c).
Perspective::Perspective(float x, float y, float z){
    pos = Point3D(x,y,z);
}  // set pos to (x, y, z)
Perspective::Perspective(const Point3D& pt){
    pos = pt;
} // set pos parallel to pt.

// Copy constuctor and assignment operator.
Perspective::Perspective(const Perspective& camera){
    pos = camera.pos;
}
Perspective& Perspective::operator= (const Perspective& other){
    pos = other.pos;
    return *this;
}

// Virtual copy constructor.
Perspective* Perspective::clone() const{
    return new Perspective(*this);
}

// Desctructor.
Perspective::~Perspective(){
}

// Get direction of projection for a point.
Vector3D Perspective::get_direction(const Point3D& p) const{
    return p-(pos);
}
