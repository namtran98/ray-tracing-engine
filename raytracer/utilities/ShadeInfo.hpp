#pragma once

#include "../materials/Material.hpp"
#include "Point3D.hpp"
#include "Ray.hpp"
#include "../world/World.hpp"
#include <memory>
/**
   This file declares the class ShadeInfo which contains all the relevant
   information for shading a point.

   Courtesy Kevin Suffern.
*/

class ShadeInfo {
public:
  bool hit;  // did the ray hit an object?
  std::unique_ptr<Material> material_ptr;  // pointer to the nearest material of the hit object.
  Point3D hit_point;  // coordinates of intersection.
  Ray ray;  // the ray that hit.
  int depth;  // recursion depth.
  float t;  // ray parameter at hit point.
  std::unique_ptr<World> w;  // pointer to the world.

public:
  // Constructor.
  ShadeInfo(World& wr);  // set the world.

  // Copy constructor.
  ShadeInfo(const ShadeInfo& sr);
  
  // Destructor.
  ~ShadeInfo();
};
