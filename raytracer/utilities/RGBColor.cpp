#include "RGBColor.hpp"
#include <algorithm>
#include <cmath>

RGBColor::RGBColor() : r(0), g(0), b(0){}
RGBColor::RGBColor(float c){
  setR(c);
  setG(c);
  setB(c);
}
RGBColor::RGBColor(float _r, float _g, float _b){
  setR(_r);
  setG(_g);
  setB(_b);
}
RGBColor::~RGBColor(){}

void RGBColor::setR(float _r){
  r = std::min((float) 1, std::max((float) 0, _r));
}

void RGBColor::setG(float _g){
  g = std::min((float) 1, std::max((float) 0, _g));
}

void RGBColor::setB(float _b){
  b = std::min((float) 1, std::max((float) 0, _b));
}

RGBColor::RGBColor(const RGBColor& c){
  r = c.r;
  g = c.g;
  b = c.b;
}

RGBColor& RGBColor::operator= (const RGBColor& rhs){
  r = rhs.r;
  g = rhs.g;
  r = rhs.r;
  return *this;
}

RGBColor RGBColor::operator+(const RGBColor& c) const{
  RGBColor ret_val;
  ret_val.setR(c.r + r);
  ret_val.setG(c.g + g);
  ret_val.setB(c.b + b);
  return ret_val;
}

RGBColor& RGBColor::operator+=(const RGBColor& c){
  setR(r + c.r);
  setG(g + c.g);
  setB(b + c.b);
  return *this;
}

RGBColor RGBColor::operator*(const float a) const {  // multiplication by a float.
  RGBColor ret_val;
  ret_val.setR(r * a);
  ret_val.setG(g * a);
  ret_val.setB(b * a);
  return ret_val;
}

RGBColor& RGBColor::operator*=(const float a){   // compound multiplication by a float.
  setR(r * a);
  setG(g * a);
  setB(b * a);
  return *this;
}

RGBColor RGBColor::operator/(const float a) const{ // division by a float.
  RGBColor ret_val;
  ret_val.setR(r / a);
  ret_val.setG(g / a);
  ret_val.setB(b / a);
  return ret_val;
}

RGBColor& RGBColor::operator/=(const float a){   // compound multiplication by a float.
  setR(r / a);
  setG(g / a);
  setB(b / a);
  return *this;
}

RGBColor RGBColor::operator*(const RGBColor& c) const { // component-wise multiplication.
  RGBColor ret_val;
  ret_val.setR(r * c.r);
  ret_val.setG(g * c.g);
  ret_val.setB(b * c.b);
  return ret_val;
}

bool RGBColor::operator==(const RGBColor& c) const { // equality.
  return r == c.r and g == c.g and b == c.b;
}

RGBColor RGBColor::powc(float p) const {// raise components to a power.
  RGBColor ret_val;
  ret_val.setR(std::pow(r, p));
  ret_val.setG(std::pow(g, p));
  ret_val.setB(std::pow(b, p));
  return ret_val;
}

float RGBColor::average(void) const { // the average of the components.
  return (r + g + b) / 3;
}

RGBColor operator* (const float a, const RGBColor& c){ // Multiplication by a float.
  return c * a;
}
