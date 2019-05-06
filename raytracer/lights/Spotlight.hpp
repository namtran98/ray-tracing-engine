#pragma once
#include "../utilities/Vector3D.hpp"
#include "Point.hpp"

/**
   This file declares the Spotlight class which represents a spotlight. It
   derives from Point light source which already has a position.

   Courtesy Kevin Suffern.
*/

class Spotlight: public Point {
private:
  Vector3D dir;  // the direction of emitted light, stored as a unit vector.
  float theta;  // the angle of the spotlight, in radians.

public:
  // Constructors.
  Spotlight();  // set color to white (1, 1, 1).
  Spotlight(float c, float ls, Point3D pos, Vector3D dir, float theta);  // set color to (c, c, c).
  Spotlight(float r, float g, float b, float ls,Point3D pos, Vector3D dir, float theta);  // set color to (r, g, b).
  Spotlight(const RGBColor& _color, float ls, Point3D pos, Vector3D dir, float theta);  // set color to _color.

  // Copy constructor and assignment operator.
  Spotlight(const Spotlight& rhs);
  Spotlight& operator= (const Spotlight& rhs);

  // Virtual copy constructor.
  virtual Spotlight* clone() const;

  // Desctructor.
  virtual ~Spotlight(void);

  // Set spotlight position and angle.
  void set_theta(float t);  // set theta to t which must be in radians.

  // Set dir parallel to supplied direction.
  void set_direction(float c);  // parallel to (c, c, c).
  void set_direction(float x, float y, float z);  // parallel to (x, y, z).
  void set_direction(const Vector3D& d);  // parallel to d.

  // Normalized direction vector from light source to hit point.
  virtual Vector3D get_direction(const ShadeInfo& sinfo) const;

  // Luminance from this light source at hit point.
  virtual RGBColor L(const ShadeInfo& sinfo) const;
};
