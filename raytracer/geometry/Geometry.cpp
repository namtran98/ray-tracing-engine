#include "Geometry.hpp"

// Constructors.

// sets material_ptr to NULL.
Geometry::Geometry() : material_ptr(NULL) {}  

// Copy constructor and assignment operator.
Geometry::Geometry(const Geometry& object) {
    material_ptr = object.material_ptr;
    bbox = object.bbox;
}

Geometry& Geometry::operator= (const Geometry& rhs) {
    material_ptr = rhs.material_ptr;
    bbox = rhs.bbox;
    return *this;
}

// Destructor.
Geometry::~Geometry() {
    delete material_ptr;
    material_ptr = NULL;
}	

// Get/set material.
Material* Geometry::get_material() const {
    return material_ptr;
}

void Geometry::set_material(Material* mPtr) {
    this->material_ptr = mPtr;
}

BBox Geometry::get_bounding_box() {
    return BBox();
}