#include "Parallel.hpp"


// Constructors.
Parallel::Parallel(){
    dir = Vector3D(0,0,-1);
}  // set dir parallel to -z (negative z) axis.
Parallel::Parallel(float c){
    dir = Vector3D(c,c,c);    
}  // set dir parallel to (c, c, c).
Parallel::Parallel(float x, float y, float z){
    dir = Vector3D(x,y,z);

}  // set dir parallel to (x, y, z)
Parallel::Parallel(const Vector3D& d){
    dir = d;
}  // set dir parallel to d.

// Copy constuctor and assignment operator.
Parallel::Parallel(const Parallel& camera){
    dir = camera.dir;
}

Parallel& Parallel::operator= (const Parallel& other){
    this->dir = other.dir;
}

// Virtual copy constructor.
Parallel* Parallel::clone() const{
    return new Parallel(*this);
}

// Desctructor.
Parallel::~Parallel(){

} 							

// Get direction of projection for a point.
Vector3D Parallel::get_direction(const Point3D& p) const{
    return dir;
}