/**
   This builds a simple scene that consists of a sphere, a triangle, and a
   plane.
   Parallel viewing is used with a single sample per pixel.
*/
#include "../cameras/Perspective.hpp"
#include "../cameras/Parallel.hpp"
#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"
#include "../materials/Cosine.hpp"
#include "../materials/Matte.hpp"
#include "../materials/Reflective.hpp"
#include "../samplers/Simple.hpp"
#include "../samplers/Jittered.hpp"
#include "../utilities/Constants.hpp"
#include "../world/World.hpp"
#include "../lights/Ambient.hpp"
#include "../lights/Point.hpp"
#include "../acceleration/BVH.hpp"

#include <random>
#include <iostream>

void
World::build(void) {
  // View plane  .
  vplane.top_left.x = -500;
  vplane.top_left.y = 500;
  vplane.top_left.z = 500;
  vplane.bottom_right.x = 500;
  vplane.bottom_right.y = -500;
  vplane.bottom_right.z = 500;
  vplane.hres = 500;
  vplane.vres = 500;

  // Background color.
  bg_color = white;

  set_camera(new Perspective(0, 0, 550));
  sampler_ptr = std::make_unique<Simple>(camera_ptr.get(), &vplane);
  set_ambient_light(new Ambient(1, 1, 1, .4));
  add_light(new Point(RGBColor(1,1,1), 10, Point3D(0,20,0)));

  std::random_device rd; // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generator
  std::uniform_int_distribution<> distr(-500, 500); // define the range
  set_acceleration(new BVH());

  int NUM_OBJECTS = 100000;

  for(int i = 0; i < NUM_OBJECTS; i++){
    int x = distr(eng);
    int y = distr(eng); 
    int z = distr(eng);
    // std::cout<<x << " "<< y<<" "<< z << "\n";
    Sphere* sphere_ptr = new Sphere(Point3D(x,y,z), 10);
    sphere_ptr->set_material(new Cosine(red));
    accel_ptr->add_object(sphere_ptr);
    // add_object(sphere_ptr);
  }
  // sphere
  
   accel_ptr->initialize();
}
