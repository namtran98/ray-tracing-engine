#include "Compound.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Constants.hpp"

// Courtesy Kevin Suffren

// Constructors
Compound::Compound() : Geometry() {}


// Copy constructor
Compound::Compound(const Compound& object) 
    : Geometry(object) {
    copy_objects(object.objects);
}


// Assignment operator
Compound& Compound::operator= (const Compound& rhs) {
    if (this == &rhs) {
        return *this;
    }

    objects = rhs.objects;
    return *this;
}


// Destructor
Compound::~Compound() {
    delete_objects();
}


Compound* Compound::clone() const{
  return new Compound(*this);
}


void Compound::add_object(Geometry* object_ptr) {
    objects.push_back(object_ptr); 
}


int Compound::get_num_objects() {
    return objects.size();
}

// Private helper member function
void Compound::delete_objects() {
    int num_objects = objects.size();

    for (int i = 0; i < num_objects; i++) {
        delete objects[i];
        objects[i] = NULL;
    }

    objects.erase(objects.begin(), objects.end());
}


void Compound::copy_objects(const std::vector<Geometry*>& rhs) {
    delete_objects();
    int num_objects = rhs.size();

    for (int i = 0; i < num_objects; i++) {
        objects.push_back(rhs[i]->clone());
    }
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
            material_ptr = objects[i]->get_material(); 
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
