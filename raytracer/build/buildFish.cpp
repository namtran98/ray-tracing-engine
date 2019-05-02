/**
   This builds a simple scene that consists of a sphere, a triangle, and a
   plane.
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

#include <iostream>
void
World::build(void) {
  // View plane  .
  vplane.top_left.x = -8;
  vplane.top_left.y = 8;
  vplane.top_left.z = 10;
  vplane.bottom_right.x = 8;
  vplane.bottom_right.y = -8;
  vplane.bottom_right.z = 10;
  vplane.hres = 400;
  vplane.vres = 400;

  // Background color.
  bg_color = white;

  // Camera and sampler.
  // set_camera(new Parallel(0, 0, -1));

  set_camera(new Perspective(0, 0, 20));
  sampler_ptr = std::make_unique<Simple>(camera_ptr.get(), &vplane);

  // will get seg fault unless add normals
  Mesh* mesher = new Mesh((char*)"goldfish_low_res.ply");

  for(int i = 0; i < mesher->num_triangles; i++){
    MeshTriangle* meshTri1 = new MeshTriangle(mesher, mesher->vertex_faces[i][0],mesher->vertex_faces[i][1],mesher->vertex_faces[i][2]);
    meshTri1->set_material(new Cosine(red));
    mesher->normals.push_back(meshTri1->compute_normal());
    add_object(meshTri1);
  }
//   MeshTriangle* meshTri1 = new MeshTriangle(mesher, mesher->vertex_faces[0][0],mesher->vertex_faces[0][1],mesher->vertex_faces[0][2]);
//   meshTri1->set_material(new Cosine(red));
//   mesher->normals.push_back(meshTri1->compute_normal());
//   add_object(meshTri1);

//   MeshTriangle* meshTri2 = new MeshTriangle(mesher, mesher->vertex_faces[1][0],mesher->vertex_faces[1][1],mesher->vertex_faces[1][2]);
//   meshTri2->set_material(new Cosine(blue));
//   mesher->normals.push_back(meshTri2->compute_normal());
//   add_object(meshTri2);
}
