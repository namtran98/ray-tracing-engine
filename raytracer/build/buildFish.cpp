/**
   This builds a simple scene that consists fish under the sea.
   Perspective viewing is used.
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
#include "../lights/Point.hpp"
#include "../lights/Ambient.hpp"

#include <iostream>
void World::build(void) {
  // View plane  .
  vplane.top_left.x = -10;
  vplane.top_left.y = 10;
  vplane.top_left.z = 10;
  vplane.bottom_right.x = 10;
  vplane.bottom_right.y = -10;
  vplane.bottom_right.z = 10;
  vplane.hres = 1000;
  vplane.vres = 1000;

  // Background color.
  bg_color = oceanBlue;

  // Camera and sampler.
  // set_camera(new Parallel(0, 0, -1));

  set_camera(new Perspective(0, 0, 20));
  sampler_ptr = std::make_unique<Jittered>(camera_ptr.get(), &vplane, 4, 83);
  set_ambient_light(new Ambient(1, 1, 1, .1));
  add_light(new Point(white, 1, Point3D(0,0,100)));

  Matte *matte_material1 = new Matte();
  // const float ka = .25;
  // const float kd = 1.0;
  matte_material1->set_ka(.8);
  matte_material1->set_kd(.8);
  matte_material1->set_cd(lightPurple);
  // will get seg fault unless add normals
  Mesh* mesher = new Mesh((char*)"../resources/goldfish_low_res.ply");

  for(int i = 0; i < mesher->num_triangles; i++){
    MeshTriangle* meshTri1 = new MeshTriangle(mesher, std::get<0>(mesher->tris[i]), std::get<1>(mesher->tris[i]), std::get<2>(mesher->tris[i]));
    meshTri1->set_material(matte_material1);
    // mesher->normals.push_back(meshTri1->compute_normal());
    add_object(meshTri1);
  }

}
