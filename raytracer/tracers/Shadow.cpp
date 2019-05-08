#include "Shadow.hpp"

#include <iostream>

Shadow::Shadow(){
    world_ptr = NULL;
}


Shadow::Shadow(World* world_pointer){
    world_ptr = world_pointer;
}


Shadow::~Shadow() {
    if (world_ptr)
        world_ptr = NULL;
}

RGBColor Shadow::trace_ray(const Ray& ray) const {
    float weight = ray.w;  // ray weight for the pixel.
    ShadeInfo sinfo = world_ptr->hit_objects(ray);
    if (sinfo.hit) {
        bool shadow = false;
        std::vector<Light*> lights = world_ptr->lights;
        //check for intersection of prims on way to light
        for (int i = 0;i<lights.size();i++){
            Vector3D dir = lights[i]->get_direction(sinfo);
            Ray shadowRay = Ray(sinfo.hit_point, dir);
            ShadeInfo sinfoshadow = world_ptr->hit_objects(shadowRay);
            shadow = sinfoshadow.hit;
        }
        if(!shadow){
            return weight * sinfo.material_ptr->shade(sinfo);
        }else{
            // add something here that uses the in shadow color
            return world_ptr->ambient_ptr->L(sinfo);
        }
    }
    return weight * world_ptr->bg_color;
}