#include "Sampler.hpp"

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

// Desctructor.
Sampler::~Sampler(){

}   							