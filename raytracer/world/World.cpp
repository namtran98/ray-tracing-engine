#include "World.hpp"
#include "../build/buildSphereGrid.cpp"


World::World(){
    vplane = ViewPlane();
    bg_color = RGBColor();
    geometry = std::vector<Geometry*>();
    lights = std::vector<Light*>();
    camera_ptr = NULL;
    sampler_ptr = NULL;
    accel_ptr = NULL;
    tracer_ptr = NULL;
    ambient_ptr = nullptr;
} // initialize members.

// Destructor.
World::~World(){

}  // free memory.

// Add to the scene.
void World::add_object(Geometry* geom_ptr){
    geometry.push_back(geom_ptr);
}
void World::add_light(Light* light_ptr){
    lights.push_back(light_ptr);
}

void World::set_ambient_light(Light *light_ptr){
  ambient_ptr = light_ptr;
}

void World::set_camera(Camera* c_ptr){
    camera_ptr = std::unique_ptr<Camera>(c_ptr);
}
// void set_ambient_light(Light* light_ptr);
void World::set_tracer(Tracer* t_ptr){
    tracer_ptr = std::unique_ptr<Tracer>(t_ptr);
}

void World::set_acceleration(Acceleration* acceleration_ptr){
    accel_ptr = std::unique_ptr<Acceleration>(acceleration_ptr);
}


// Returns appropriate shading information corresponding to intersection of
// the ray with the scene geometry.
ShadeInfo World::hit_objects(const Ray& ray){
    ShadeInfo sinfo = ShadeInfo(*this);
    if (accel_ptr == nullptr) {
        float t = kHugeValue;
        for (const auto& shape: geometry){
            ShadeInfo temp_sinfo = ShadeInfo(*this);
            float tempt = 0.0f;
            if(shape->hit(ray, tempt, temp_sinfo) && tempt < t ){
                t = tempt;
                sinfo = temp_sinfo;
            }
        }
    }
    else {
        if (accel_ptr->hit(ray, sinfo)) {
            return sinfo;
        }
    }
    return sinfo;
}
