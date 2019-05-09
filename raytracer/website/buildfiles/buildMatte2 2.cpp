/**
   This builds a simple scene that consists fish under the sea.
   Perspective viewing is used.
*/
#include "../cameras/Perspective.hpp"
#include "../cameras/Parallel.hpp"
#include "../materials/Matte.hpp"
#include "../materials/Reflective.hpp"
#include "../samplers/Simple.hpp"
#include "../samplers/Jittered.hpp"
#include "../utilities/Constants.hpp"
#include "../world/World.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Plane.hpp"
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
  bg_color = grey;

  // Camera and sampler.
  // set_camera(new Parallel(0, 0, -1));

  set_camera(new Perspective(0, 0, 20));
  sampler_ptr = std::make_unique<Jittered>(camera_ptr.get(), &vplane, 4, 83);
  set_ambient_light(new Ambient(1, 1, 1, .7));
  add_light(new Point(white, 1, Point3D(0,10,0)));
  add_light(new Point(white, 1, Point3D(10,10,10)));

  Matte *matte_material1 = new Matte();
  matte_material1->set_ka(.8);
  matte_material1->set_kd(.8);
  matte_material1->set_cd(yellow);

  Matte *matte_material2 = new Matte();
  matte_material2->set_ka(.5);
  matte_material2->set_kd(.5);
  matte_material2->set_cd(lightGreen);
  


  Matte *matte_material3 = new Matte();
  matte_material3->set_ka(.3);
  matte_material3->set_kd(.3);
  matte_material3->set_cd(skyBlue);

  Matte *matte_material4 = new Matte();
  matte_material4->set_ka(.9);
  matte_material4->set_kd(.9);
  matte_material4->set_cd(grey);

  Matte *matte_material5 = new Matte();
  matte_material5->set_ka(.9);
  matte_material5->set_kd(.9);
  matte_material5->set_cd(lightPurple);


  Reflective *reflective_material = new Reflective();
  reflective_material->set_ka(.3);
  reflective_material->set_kd(.3);
  reflective_material->set_cd(red);
  reflective_material->set_cr(1);
  reflective_material->set_kr(1);



  Sphere* sphere_ptr1 = new Sphere(Point3D(-3, 2, 0), 5);
  sphere_ptr1->set_material(matte_material1);  
  add_object(sphere_ptr1);

  Sphere* sphere_ptr2 = new Sphere(Point3D(-3, 2, 8), 2);
  sphere_ptr2->set_material(matte_material2); 
  add_object(sphere_ptr2);

  Sphere* sphere_ptr3 = new Sphere(Point3D(5, 3, 0), 3);
  sphere_ptr3->set_material(reflective_material);  
  add_object(sphere_ptr3);


  Plane* plane_ptr = new Plane(Point3D(0,0,-10), Vector3D(0, 0, 1));
  plane_ptr->set_material(matte_material4);  // green
  add_object(plane_ptr);

  Plane* plane_ptr2 = new Plane(Point3D(0,-4,0), Vector3D(0, 5, 2));
  plane_ptr2->set_material(matte_material5);  // green
  add_object(plane_ptr2);
}
