#include "Sampler.hpp"
#include "../world/ViewPlane.hpp"
#include "../utilities/Constants.hpp"

Sampler::Sampler(){
    camera_ptr = NULL;
    viewplane_ptr = NULL;
}  // initializes members to NULL.
Sampler::Sampler(Camera* c_ptr, ViewPlane* v_ptr){
    camera_ptr = c_ptr;
    viewplane_ptr = v_ptr;
}  // set members.

// Copy constuctor and assignment operator.
Sampler::Sampler(const Sampler& camera){
    camera_ptr = camera.camera_ptr;
    viewplane_ptr = camera.viewplane_ptr;
}

Sampler& Sampler::operator= (const Sampler& other){
    this->camera_ptr = other.camera_ptr;
    this->viewplane_ptr = other.viewplane_ptr;
    return *this;
}

Point3D Sampler::screenCoordsToPoint(float px, float py) const{
  float pixelWidth = (viewplane_ptr-> bottom_right.x - viewplane_ptr->top_left.x)/viewplane_ptr->hres;
  float pixelHeight = (viewplane_ptr->top_left.y - viewplane_ptr->bottom_right.y)/viewplane_ptr->vres;
  Point3D point = Point3D(px * pixelWidth + (viewplane_ptr->top_left.x), py * pixelHeight + (viewplane_ptr->bottom_right.y), viewplane_ptr->top_left.z-kEpsilon);
  return point;
}

// Desctructor.
Sampler::~Sampler(){

}
