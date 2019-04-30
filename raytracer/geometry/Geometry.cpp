#include "Geometry.hpp"

// Constructors.
Geometry::Geometry(){
  material_ptr = NULL;
}  // sets material_ptr to NULL.

// Copy constructor and assignment operator.
Geometry::Geometry(const Geometry& object){
  material_ptr = object.material_ptr;
  bbox = object.bbox;
}
Geometry& Geometry::operator= (const Geometry& rhs){
  material_ptr = rhs.material_ptr;
  bbox = rhs.bbox;
  return *this;
}

// Destructor.
Geometry::~Geometry(){
}

// Get/set material.
Material* Geometry::get_material() const{
    return material_ptr;
}
void Geometry::set_material(Material* mPtr){
    this->material_ptr = mPtr;
}
