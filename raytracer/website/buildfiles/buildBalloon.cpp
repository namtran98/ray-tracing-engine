/**
   This builds a simple scene that consists fish under the sea.
   Perspective viewing is used.
*/
#include "../cameras/Perspective.hpp"
#include "../cameras/Parallel.hpp"
#include "../materials/Cosine.hpp"
#include "../materials/Matte.hpp"
#include "../materials/Reflective.hpp"
#include "../samplers/Simple.hpp"
#include "../samplers/Jittered.hpp"
#include "../utilities/Constants.hpp"
#include "../world/World.hpp"
#include "../utilities/Mesh.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"
#include "../geometry/MeshTriangle.hpp"
#include "../acceleration/BVH.hpp"
#include "../lights/Point.hpp"
#include "../lights/Directional.hpp"
#include "../lights/Ambient.hpp"

#include <iostream>
void World::build(void) {
  // View plane.
  vplane.top_left.x = -1000;
  vplane.top_left.y = 1000;
  vplane.top_left.z = 1000;
  vplane.bottom_right.x = 1000;
  vplane.bottom_right.y = -1000;
  vplane.bottom_right.z = 1000;
  vplane.hres = 500;
  vplane.vres = 500;

  // vplane.top_left.x = -400;
  // vplane.top_left.y = 400;
  // vplane.top_left.z = 50;
  // vplane.bottom_right.x = 400;
  // vplane.bottom_right.y = -400;
  // vplane.bottom_right.z = 50;
  // vplane.hres = 400;
  // vplane.vres = 400;

  // Background color.
  bg_color = nightBlue;

  // Camera and sampler.
  set_camera(new Parallel());

  // set_camera(new Perspective(0, 0, 600)); //9 //15 //25
  sampler_ptr = std::make_unique<Simple>(camera_ptr.get(), &vplane);
  set_ambient_light(new Ambient(1, 1, 1, .5));
  add_light(new Point(white, .05, Point3D(0,0,200)));
  // add_light(new Directional(sunYellow, .4, Vector3D(0, 1, 0)));

  set_acceleration(new BVH());

  // First hot air balloon
  Mesh* mesher = new Mesh((char*)"../resources/balloonRotate.ply", 650, -500, -30); //30, -30, 0
  Matte *matte_material = new Matte();
  matte_material->set_ka(.5);
  matte_material->set_kd(.5);
  matte_material->set_cd(oceanBlue);

  accel_ptr->add_from_mesh(mesher, matte_material);
  accel_ptr->compute_normals(mesher);

  // Second hot air balloon
  Mesh* mesher2 = new Mesh((char*)"../resources/balloonRotate.ply", -600, 300, -10); //30, -30, 0
  Matte *matte_material2 = new Matte();
  matte_material2->set_ka(.5);
  matte_material2->set_kd(.5);
  matte_material2->set_cd(brown);

  accel_ptr->add_from_mesh(mesher2, matte_material2);
  accel_ptr->compute_normals(mesher2);

  // First teapot
  Mesh* mesher3 = new Mesh((char*)"../resources/teapotScale.ply", 600, -310, -30); //600, -310, -30
  Reflective *reflectiveMat = new Reflective();
  reflectiveMat->set_kr(.5);
  reflectiveMat->set_ka(.5);
  reflectiveMat->set_kd(.5);
  reflectiveMat->set_cr(lightPurple);
  reflectiveMat->set_cd(white);

  accel_ptr->add_from_mesh(mesher3, reflectiveMat);
  accel_ptr->compute_normals(mesher3);

  // Second teapot
  Mesh* mesher4 = new Mesh((char*)"../resources/teapotScale.ply", -650, 490, -30); //600, -310, -30
  Reflective *reflectiveMat2 = new Reflective();
  reflectiveMat2->set_kr(.5);
  reflectiveMat2->set_ka(.5);
  reflectiveMat2->set_kd(.5);
  reflectiveMat2->set_cr(lightPurple);
  reflectiveMat2->set_cd(white);

  accel_ptr->add_from_mesh(mesher4, reflectiveMat2);
  accel_ptr->compute_normals(mesher4);

  // Airplane
  Mesh* mesher5 = new Mesh((char*)"../resources/airplane.ply", -300, -900, -30); //600, -310, -30
  Matte *matte_material3 = new Matte();
  matte_material3->set_ka(.5);
  matte_material3->set_kd(.5);
  matte_material3->set_cd(grey);

  accel_ptr->add_from_mesh(mesher5, matte_material3);
  accel_ptr->compute_normals(mesher5);
  
  // First goose
  Mesh* mesher6 = new Mesh((char*)"../resources/goose.ply", -400, -400, -30);
  Matte *matte_goose = new Matte();
  matte_goose->set_ka(.5);
  matte_goose->set_kd(.5);
  matte_goose->set_cd(brown);

  accel_ptr->add_from_mesh(mesher6, matte_goose);
  accel_ptr->compute_normals(mesher6);

  // Second goose
  Mesh* mesher7 = new Mesh((char*)"../resources/goose.ply", -470, -450, -30); 

  accel_ptr->add_from_mesh(mesher7, matte_goose);
  accel_ptr->compute_normals(mesher7);

  // Third goose
  Mesh* mesher8 = new Mesh((char*)"../resources/goose.ply", -560, -500, -30);

  accel_ptr->add_from_mesh(mesher8, matte_goose);
  accel_ptr->compute_normals(mesher8);

  // Fourth goose
  Mesh* mesher9 = new Mesh((char*)"../resources/goose.ply", -660, -450, -30); 

  accel_ptr->add_from_mesh(mesher9, matte_goose);
  accel_ptr->compute_normals(mesher9);

  // Fifth goose
  Mesh* mesher10 = new Mesh((char*)"../resources/goose.ply", -720, -400, -30);

  accel_ptr->add_from_mesh(mesher10, matte_goose);
  accel_ptr->compute_normals(mesher10);


  accel_ptr->initialize();

  
}