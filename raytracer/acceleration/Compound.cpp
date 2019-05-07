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
        objects[i] = nullptr;
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
    bool hit = false;
    t_min = kHugeValue;
    int num_objects = objects.size();
    ShadeInfo temp_si(*sinfo.w);
    for (int i = 0; i < num_objects; i++) {
        if (objects[i]->hit(ray, t, temp_si) && (t < t_min)) {
            hit = true;
            t_min = t;
            sinfo = ShadeInfo(temp_si);
            sinfo.material_ptr = objects[i]->get_material();
        }
    }
    return (hit);
}
