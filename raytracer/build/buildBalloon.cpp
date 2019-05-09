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
  bg_color = skyBlue;

  // Camera and sampler.
  set_camera(new Parallel());

  // set_camera(new Perspective(0, 0, 600)); //9 //15 //25
  sampler_ptr = std::make_unique<Simple>(camera_ptr.get(), &vplane);
  set_ambient_light(new Ambient(1, 1, 1, .5));
  add_light(new Point(sunYellow, .8, Point3D(0,0,200)));
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
  
  accel_ptr->initialize();

  // // spheres
  // Sphere* sphere_ptr1 = new Sphere(Point3D(-20, 30, -30), 20);
  // sphere_ptr1->set_material(new Cosine(oceanBlue)); 
  // add_object(sphere_ptr1);

  // Sphere* sphere_ptr2 = new Sphere(Point3D(-10, 30, -30), 20);
  // sphere_ptr2->set_material(new Cosine(brown));  
  // add_object(sphere_ptr2);

  // Sphere* sphere_ptr3 = new Sphere(Point3D(0, 30, -30), 20);
  // sphere_ptr3->set_material(new Cosine(darkGreen));  
  // add_object(sphere_ptr3);

  // Sphere* sphere_ptr4 = new Sphere(Point3D(10, 30, -30), 20);
  // sphere_ptr4->set_material(new Cosine(orange));  
  // add_object(sphere_ptr4);

  // Sphere* sphere_ptr5 = new Sphere(Point3D(20, 30, -30), 20);
  // sphere_ptr5->set_material(new Cosine(green)); 
  // add_object(sphere_ptr5);

  // // Second layering
  // Sphere* sphere_ptr6 = new Sphere(Point3D(-20, 35, -25), 20);
  // sphere_ptr6->set_material(new Cosine(green)); 
  // add_object(sphere_ptr6);

  // Sphere* sphere_ptr7 = new Sphere(Point3D(-10, 35, -25), 20);
  // sphere_ptr7->set_material(new Cosine(orange)); 
  // add_object(sphere_ptr7);

  // Sphere* sphere_ptr8 = new Sphere(Point3D(0, 35, -25), 20);
  // sphere_ptr8->set_material(new Cosine(darkGreen));
  // add_object(sphere_ptr8);

  // Sphere* sphere_ptr9 = new Sphere(Point3D(10, 35, -25), 20);
  // sphere_ptr9->set_material(new Cosine(brown));  
  // add_object(sphere_ptr9);

  // Sphere* sphere_ptr10 = new Sphere(Point3D(20, 35, -25), 20);
  // sphere_ptr10->set_material(new Cosine(oceanBlue));  
  // add_object(sphere_ptr10);

  // //Triangles
  // Point3D a(5, -10, 0);
  // Point3D b(11, 5, 0);
  // Point3D c(8.3, 0, 0);
  // Triangle* triangle_ptr1 = new Triangle(a, b, c);
  // triangle_ptr1->set_material(new Cosine(black));
  // add_object(triangle_ptr1);

  // Point3D d(-5, -10, 0);
  // Point3D e(-11, 5, 0);
  // Point3D f(-8.3, 0, 0);
  // Triangle* triangle_ptr2 = new Triangle(d, e, f);
  // triangle_ptr2->set_material(new Cosine(black));
  // add_object(triangle_ptr2);
}