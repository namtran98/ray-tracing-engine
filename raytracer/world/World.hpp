#pragma once
#include "utilities/RGBColor.hpp"
#include "utilities/ShadeInfo.hpp"
#include "ViewPlane.hpp"
#include "../cameras/Camera.hpp"
#include "../samplers/Sampler.hpp"
#include "../geometry/Geometry.hpp"
#include "../lights/Light.hpp"
#include <vector>
#include <memory>
/**
   This file declares the World class which contains all the information about
   the scene - geometry and materials, lights, viewplane, camera, samplers, and
   acceleration structures.

   It also traces rays through the scene.

   Courtesy Kevin Suffern.
*/

class World {
public:
  ViewPlane vplane;
  RGBColor bg_color;
  std::vector<Geometry*> geometry;
  std::vector<Light*> lights;
  std::unique_ptr<Camera> camera_ptr;
  std::unique_ptr<Sampler> sampler_ptr;

  // Light* ambient_ptr;
  // Tracer* tracer_ptr;
  // Acceleration* ;

public:
  // Constructors.
  World();  // initialize members.

  // Destructor.
  ~World();  // free memory.

  // Add to the scene.
  void add_object(Geometry* geom_ptr);
  void add_light(Light* light_ptr);
  void set_camera(Camera* c_ptr);
  // void set_ambient_light(Light* light_ptr);
  // void set_tracer(Tracer* tracer_ptr);
  // void set_acceleration(Acceleration* acceleration_ptr);

  // Build scene - add all geometry, materials, lights, viewplane, camera,
  // samplers, and acceleration structures
  void build(void);

  // Returns appropriate shading information corresponding to intersection of
  // the ray with the scene geometry.
  ShadeInfo hit_objects(const Ray& ray);
};
