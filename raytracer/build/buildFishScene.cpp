/**
   This builds a simple scene that consists of fish underwater.
   Parallel viewing is used with a single sample per pixel.
*/
#include "../cameras/Perspective.hpp"
#include "../cameras/Parallel.hpp"
#include "../materials/Cosine.hpp"
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
  bg_color = blue;

  // Camera and sampler.
  // set_camera(new Parallel(0, 0, -1));

  set_camera(new Perspective(0, 0, 100));
  sampler_ptr = std::make_unique<Jittered>(camera_ptr.get(), &vplane, 4, 83);

  set_acceleration(new BVH());

  Mesh* fish1 = new Mesh((char*)"../resources/goldfish_low_res.ply");
  accel_ptr->add_from_mesh(fish1, new Cosine(red));
  accel_ptr->compute_normals(fish1);

  // Offset of x=10, with only two fish seems to compile okay
  Mesh* fish2 = new Mesh((char*)"../resources/goldfish_low_res.ply", 10, 0, 0);
  accel_ptr->add_from_mesh(fish2, new Cosine(blue));
  accel_ptr->compute_normals(fish2);

  // Anything added after this seems to segfault

  // Mesh* fish3 = new Mesh((char*)"../resources/goldfish_low_res.ply", -15, 0, 0);
  // accel_ptr->add_from_mesh(fish3, new Cosine(green));
  // accel_ptr->compute_normals(fish3);

  // Mesh* fish4 = new Mesh((char*)"../resources/goldfish_low_res.ply", 3, 0, 0);
  // accel_ptr->add_from_mesh(fish4, new Cosine(yellow));
  // accel_ptr->compute_normals(fish4);


  accel_ptr->initialize();

}
