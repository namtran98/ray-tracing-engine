/**
   This builds a simple scene that consists of a sphere, a triangle, and a
   plane.
   Parallel viewing is used with a single sample per pixel.
*/
#include "../cameras/Perspective.hpp"
#include "../cameras/Parallel.hpp"
#include "../materials/Matte.hpp"
#include "../samplers/Simple.hpp"
#include "../samplers/Jittered.hpp"
#include "../utilities/Constants.hpp"
#include "../world/World.hpp"
#include "../utilities/Mesh.hpp"
#include "../geometry/MeshTriangle.hpp"
#include "../acceleration/BVH.hpp"
#include "../lights/Point.hpp"
#include "../lights/Ambient.hpp"

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
  bg_color = oceanBlue;
  set_ambient_light(new Ambient(1, 1, 1, .3));
  add_light(new Point(white, 1, Point3D(10,10,10)));

  // Camera and sampler.
  // set_camera(new Parallel(0, 0, -1));

  Matte *matte_material1 = new Matte();
  matte_material1->set_ka(.8);
  matte_material1->set_kd(.8);
  matte_material1->set_cd(lightPurple);

  set_camera(new Perspective(0, 0, 20));
  sampler_ptr = std::make_unique<Jittered>(camera_ptr.get(), &vplane, 4, 83);

  set_acceleration(new BVH());

  Mesh* mesher = new Mesh((char*)"../resources/goldfish_low_res.ply");

  accel_ptr->add_from_mesh(mesher,matte_material1);
  accel_ptr->compute_normals(mesher);

  accel_ptr->initialize();

}
