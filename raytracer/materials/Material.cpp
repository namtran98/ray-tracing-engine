#include "Material.hpp"

// Constructors.
Material::Material(){

}  // does nothing.

// Copy constuctor and assignment operator.
Material::Material(const Material& other){}

Material& Material::operator=(const Material& other){
    return *this;
}


// Desctructor.
Material::~Material(){}

// Shade to make the linker work
RGBColor Material::shade(const ShadeInfo& sinfo) const {
  return RGBColor();
}
