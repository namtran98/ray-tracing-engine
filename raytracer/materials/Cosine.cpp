#include "Cosine.hpp"

Cosine::Cosine(){
    color = RGBColor(0);
}  // set color to (0, 0, 0).
Cosine::Cosine(float c){
    color = RGBColor(c);
}  // set color to (c, c, c).
Cosine::Cosine(float r, float g, float b){
    color = RGBColor(r,g,b);
}  // set color to (r, g, b).
Cosine::Cosine(const RGBColor& c){
    color = c;
}  // set color to c.

// Copy constuctor and assignment operator.
Cosine::Cosine(const Cosine& other){
    color = other.color;
}
Cosine& Cosine::operator= (const Cosine& other){
    this-> color = other.color;
    return *this;
}

// Virtual copy constructor.
Cosine* Cosine::clone() const{
    return new Cosine(*this);
}

// Desctructor.
Cosine::~Cosine(){

}

/* Returned shade is: color * cos \theta.
    \theta is the angle between the normal at the hit point and the ray.
    Assuming unit vectors, cos \theta = dot product of normal and -ray.dir.
*/
RGBColor Cosine::shade(const ShadeInfo& sinfo) const{
    Vector3D normal_copy = sinfo.normal;
    Vector3D ray_copy = sinfo.ray.d;
    normal_copy.normalize();
    ray_copy.normalize();
    return color*(normal_copy * (-ray_copy));
}
