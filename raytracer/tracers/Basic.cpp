#include "Basic.hpp"
#include <iostream>
#include <string>
#include <sstream>



Basic::Basic(){
    world_ptr = NULL;
}


Basic::Basic(World* world_pointer){
    world_ptr = world_pointer;
}


Basic::~Basic() {
    if (world_ptr)
        world_ptr = NULL;
}

RGBColor Basic::trace_ray(const Ray& ray) const {
    float weight = ray.w;  // ray weight for the pixel.
    ShadeInfo sinfo = world_ptr->hit_objects(ray);
    if (sinfo.hit) {
        return weight * sinfo.material_ptr->shade(sinfo);
        cout << "here";
    }
    else {
        return weight * world_ptr->bg_color;
    }
}