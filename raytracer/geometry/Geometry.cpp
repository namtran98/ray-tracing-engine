#include "Geometry.hpp"

// Constructors.
Geometry::Geometry(){
    material_ptr = NULL;
}  // sets material_ptr to NULL.

// Copy constructor and assignment operator.
Geometry::Geometry(const Geometry& object){
    
}

Geometry& Geometry::operator= (const Geometry& rhs){
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
