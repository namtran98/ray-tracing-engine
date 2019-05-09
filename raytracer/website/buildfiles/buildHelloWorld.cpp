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


void
World::build(void) {
  // View plane  .
  vplane.top_left.x = -10;
  vplane.top_left.y = 10;
  vplane.top_left.z = 10;
  vplane.bottom_right.x = 10;
  vplane.bottom_right.y = -10;
  vplane.bottom_right.z = 10;
  vplane.hres = 400;
  vplane.vres = 400;

  // Background color.
  bg_color = black;

  // Camera and sampler.
  // set_camera(new Parallel(0, 0, -1));

  set_camera(new Perspective(0, 0, 20));
  sampler_ptr = std::make_unique<Jittered>(camera_ptr.get(), &vplane, 4, 100);
  set_ambient_light(new Ambient(1, 1, 1, .4));
  add_light(new Point(RGBColor(1,1,1), 10, Point3D(0,20,0)));

  // set_acceleration(new BVH());

  // Matte *matte_material = new Matte();
  // const float ka = .25;
  // const float kd = 1.0;
  // matte_material->set_ka(.5);
  // matte_material->set_kd(.5);
  // matte_material->set_cd(.5);

  Reflective *reflective_material = new Reflective();
  reflective_material->set_ka(.3);
  reflective_material->set_kd(.3);
  reflective_material->set_cd(red);
  reflective_material->set_cr(1);
  reflective_material->set_kr(1);

  // sphere
  Sphere* sphere_ptr = new Sphere(Point3D(-3, 2, 0), 5);
  sphere_ptr->set_material(reflective_material);
  // accel_ptr->add_object(sphere_ptr);
  add_object(sphere_ptr);

 Matte *matte_material1 = new Matte();
  // const float ka = .25;
  // const float kd = 1.0;
  matte_material1->set_ka(.8);
  matte_material1->set_kd(.8);
  matte_material1->set_cd(lightPurple);
    // sphere
  Sphere* sphere_ptr1 = new Sphere(Point3D(-3, 2, 8), 2);
  sphere_ptr1->set_material(matte_material1);
  // accel_ptr->add_object(sphere_ptr1);
  add_object(sphere_ptr1);

  // triangle
  Point3D a(2.5, -5, 1);
  Point3D b(14, -1, 0);
  Point3D c(8.5, 5, 0.5);
  Triangle* triangle_ptr = new Triangle(a, b, c);
  triangle_ptr->set_material(matte_material1);
  // accel_ptr->add_object(triangle_ptr);
  add_object(triangle_ptr);

  Matte *matte_material = new Matte();
  // const float ka = .25;
  // const float kd = 1.0;
  matte_material->set_ka(.8);
  matte_material->set_kd(.8);
  matte_material->set_cd(1,1,0);
  // plane
  Plane* plane_ptr = new Plane(Point3D(0,-4,0), Vector3D(0, 5, 2));
  plane_ptr->set_material(matte_material);  // green
  add_object(plane_ptr);



  //  accel_ptr->initialize();
}
