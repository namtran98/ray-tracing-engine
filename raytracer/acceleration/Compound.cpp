#include "Compound.hpp"
#include "../utilities/Point3D.hpp"

// Courtesy Kevin Suffren

void Compound::add_object(const Geometry* object_ptr) {
    objects.push_back(object_ptr);   // Need to check type 
}

void Compound::set_material(const Material* mPtr) {
    int num_objects = objects.size();
    for (int i = 0; i < num_objects; i++) {
        objects[i]->set_material(material_ptr);
    }
}

bool Compound::hit(const Ray& ray, double& t_min, ShadeInfo& s) const {
    float t;
    Vector3D n;
    Point3D local_hit_point;
    bool hit = false;
    //t_min = kHugeValue;               // Need to find where this constant was declared
    int num_objects = objects.size();

    for (int i = 0; i < num_objects; i++) {
        if (objects[i]->hit(ray, t, s) && (t < t_min)) {
            hit = true;
            t_min = t;
            material_ptr = objects[i]->get_material();   // Need to check value mismatch
            n = s.normal;
            local_hit_point = s.hit_point;
        }
    }
    
    if (hit) {
        s.t = t_min;
        s.normal = n;
        s.hit_point = local_hit_point;
    }

    return (hit);
} 

bool Compound::shadow_hit(const Ray& ray, double& t_min) const {

}



