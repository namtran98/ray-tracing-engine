#pragma once

#include "Point3D.hpp"
#include "Ray.hpp"
// #include "../world/World.hpp"
#include <memory>

class World;
/**
   This file declares the class ShadeInfo which contains all the relevant
   information for shading a point.

   Courtesy Kevin Suffern.
*/

class Material;

class ShadeInfo {
public:
  bool hit;  // did the ray hit an object?
  Material* material_ptr;  // pointer to the nearest material of the hit object.
  Point3D hit_point;  // coordinates of intersection.
  Point3D local_hit_point; //for texture mapping
  Ray ray;  // the ray that hit.
  int depth;  // recursion depth.
  float t;  // ray parameter at hit point.
  World* w;  // pointer to the world.
  Vector3D normal; // normal at the hit point; I added this bc we need normal to calc the shade later
  Vector3D dir;

public:
  // Constructor.
  ShadeInfo(World& wr);  // set the world.

  // Copy constructor.
  ShadeInfo(const ShadeInfo& sr);

  // Destructor.
  ~ShadeInfo();
};
