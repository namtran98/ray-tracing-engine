/**
   This builds a simple scene that consists of a sphere, a triangle, and a
   plane.
   Parallel viewing is used with a single sample per pixel.
*/
#include "../cameras/Perspective.hpp"
#include "../cameras/Parallel.hpp"
#include "../materials/Reflective.hpp"
#include "../samplers/Simple.hpp"
#include "../samplers/Jittered.hpp"
#include "../utilities/Constants.hpp"
#include "../world/World.hpp"
#include "../utilities/Mesh.hpp"
#include "../geometry/MeshTriangle.hpp"
#include "../acceleration/BVH.hpp"

#include <iostream>
void
World::build(void) {
  // View plane  .
  vplane.top_left.x = -10;
  vplane.top_left.y = 10;
  vplane.top_left.z = 10;
  vplane.bottom_right.x = 10;
  vplane.bottom_right.y = -10;
  vplane.bottom_right.z = 10;
  vplane.hres = 500;
  vplane.vres = 500;

  // Background color.
  bg_color = white;

  // Camera and sampler.
  // set_camera(new Parallel(0, 0, -1));

  set_camera(new Perspective(0, 0, 20));
  sampler_ptr = std::make_unique<Jittered>(camera_ptr.get(), &vplane, 4, 83);

  Reflective* ref_material = new Reflective();
  // ref_material->set_kr(.5);
  // ref_material->set_kd(.5);
  // ref_material->set_cr(.5);
  // const float ka = .25;
  // const float kd = 1.0;
  // ref_material->set_ka(.5);
  // ref_material->set_kd(.5);
  // ref_material->set_cd(.5);

  set_acceleration(new BVH());

  Mesh* mesher = new Mesh((char*)"../resources/goldfish_low_res.ply");

  accel_ptr->add_from_mesh(mesher, ref_material);
  accel_ptr->compute_normals(mesher);

  accel_ptr->initialize();

}
