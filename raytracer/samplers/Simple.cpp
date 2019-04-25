#include "Simple.hpp" 

Simple::Simple(){
    camera_ptr = NULL;
    viewplane_ptr = NULL;
}  // initializes members to NULL.

Simple::Simple(Camera* c_ptr, ViewPlane* v_ptr){
    camera_ptr = std::make_unique<Camera>(c_ptr);
    viewplane_ptr = std::make_unique<ViewPlane>(v_ptr);
}  // set members.

// Copy constuctor and assignment operator.
Simple::Simple(const Simple& camera){
    camera_ptr = std::make_unique<Camera>(camera.camera_ptr);
    viewplane_ptr = std::make_unique<ViewPlane>(camera.viewplane_ptr);
}

Simple& Simple::operator= (const Simple& other){
    this->camera_ptr = std::make_unique<Camera>(other.camera_ptr);
    this->viewplane_ptr = std::make_unique<ViewPlane>(other.viewplane_ptr);
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
    std::vector<Ray> rays = {};
    Point3D point = Point3D(px+.5, py+.5,-.0001);
    Ray new_ray = Ray(point, camera_ptr->get_direction(point));
    std::vector<Ray> rays = {new_ray};
    return rays;
}