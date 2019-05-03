#include "Compound.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Constants.hpp"

// Courtesy Kevin Suffren

// Constructors
Compound::Compound() {

}

// Copy constructor
Compound::Compound(const Compound& object) {

}

// Assignment operator
Compound& Compound::operator= (const Compound& rhs) {
    objects = rhs.objects;
    return *this;
}

// Destructor
Compound::~Compound() {

}

Compound* Compound::clone() const{
  return new Compound(*this);
}

void Compound::add_object(Geometry* object_ptr) {
    objects.push_back(object_ptr); 
}

void Compound::set_material(Material* mPtr) {
    int num_objects = objects.size();
    for (int i = 0; i < num_objects; i++) {
        objects[i]->set_material(mPtr);
    }
}

bool Compound::hit(const Ray& ray, float& t_min, ShadeInfo& sinfo) const {
    float t;
    Vector3D n;
    Point3D local_hit_point;
    bool hit = false;
    t_min = kHugeValue;          
    int num_objects = objects.size();

    for (int i = 0; i < num_objects; i++) {
        if (objects[i]->hit(ray, t, sinfo) && (t < t_min)) {
            hit = true;
            t_min = t;
            sinfo.material_ptr = objects[i]->get_material();  // Need to check if s.material_ptr is correct
            n = sinfo.normal;
            local_hit_point = sinfo.hit_point;
        }
    }
    
    if (hit) {
        sinfo.t = t_min;
        sinfo.normal = n;
        sinfo.hit_point = local_hit_point;
    }

    return (hit);
} 

bool Compound::shadow_hit(const Ray& ray, double& t_min) const {
    // fix later?
    return false;
}



