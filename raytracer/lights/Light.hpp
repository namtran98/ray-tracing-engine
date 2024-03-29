#pragma once
#include "../utilities/RGBColor.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Vector3D.hpp"

/**
   This file declares the Light class which is an abstract class representing a
   generic light source. Concrete light sources will be derive from this class.

   Courtesy Kevin Suffern.
*/

class Light {
protected:
  RGBColor color;  // the light's color.

public:
  // Constructors.
  Light();  // set color to white (1, 1, 1).
  Light(float c);  // set color to (c, c, c).
  Light(float r, float g, float b);  // set color to (r, g, b).
  Light(const RGBColor& _color);  // set color to _color.

  // Copy constructor and assignment operator.
  Light(const Light& rhs);
  Light& operator= (const Light& rhs);

  // Virtual copy constructor.
  virtual Light* clone() const = 0;

  // Desctructor.
  virtual ~Light(void);  // dummy function.

  // Set color.
  void set_color(const float c);  // to (c, c, c)
  void set_color(float r, float g, float b);  // to (r, g, b).
  void set_color(const RGBColor& _color);  // to _color.

  // Normalized direction vector from light source to hit point.
  virtual Vector3D get_direction(const ShadeInfo& sinfo) const = 0;

  // Luminance from this light source at hit point.
  virtual RGBColor L(const ShadeInfo& sinfo) const = 0;
};
