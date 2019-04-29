#include "Light.hpp"

Light::Light() : color(1) {}
Light::Light(float c) : color(c) {}
Light::Light(float r, float g, float b) : color(r,g,b) {}
Light::Light(const RGBColor& _color) : color(_color) {}
Light::Light(const Light& rhs) : color (rhs.color){}
Light& Light::operator= (const Light& rhs){
  color = rhs.color;
  return *this;
}
Light::~Light(){}

void Light::set_color(const float c){ // to (c, c, c)
  color = RGBColor(c);
}
void Light::set_color(float r, float g, float b){  // to (r, g, b).
  color = RGBColor(r,g,b);
}
void Light::set_color(const RGBColor& _color){  // to _color.
  color = _color;
}
