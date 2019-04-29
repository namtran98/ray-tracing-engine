#include "Simple.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Point3D.hpp"
#include "../world/ViewPlane.hpp"

Simple::Simple(){
    camera_ptr = NULL;
    viewplane_ptr = NULL;
}  // initializes members to NULL.

Simple::Simple(Camera* c_ptr, ViewPlane* v_ptr){
    camera_ptr = c_ptr;
    viewplane_ptr = v_ptr;
}  // set members.

// Copy constuctor and assignment operator.
Simple::Simple(const Simple& camera){
    camera_ptr = camera.camera_ptr;
    viewplane_ptr = camera.viewplane_ptr;
}

Simple& Simple::operator= (const Simple& other){
    this->camera_ptr = other.camera_ptr;
    this->viewplane_ptr = other.viewplane_ptr;
    return *this;
}

// Virtual copy constructor.
Simple* Simple::clone() const{
    return new Simple(*this);
}

// Desctructor.
Simple::~Simple(){

}

// Shoot a ray of weight 1 through the center of the pixel.
std::vector<Ray> Simple::get_rays(int px, int py) const{
    // float offsetX = 1/viewplane_ptr->hres;
    // float offsetY = 1/viewplane_ptr->vres;
    float pixelWidth = (viewplane_ptr-> bottom_right.x - viewplane_ptr->top_left.x)/viewplane_ptr->hres;
    float pixelHeight = (viewplane_ptr->top_left.y - viewplane_ptr->bottom_right.y)/viewplane_ptr->vres;
    Point3D point = Point3D(px*pixelWidth+(viewplane_ptr->top_left.x), py*pixelHeight + (viewplane_ptr->bottom_right.y),viewplane_ptr->top_left.z-kEpsilon);
    Ray new_ray = Ray(point, camera_ptr->get_direction(point));
    std::vector<Ray> rays = {new_ray};
    return rays;
}
