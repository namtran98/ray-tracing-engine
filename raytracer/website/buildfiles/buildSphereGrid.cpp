#include "../cameras/Parallel.hpp"
#include "../cameras/Perspective.hpp"
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
  set_camera(new Parallel(0, 0, -1));
//   set_camera(new Perspective(0, 0, 10));

  sampler_ptr = std::make_unique<Jittered>(camera_ptr.get(), &vplane, 4, 83);
  set_ambient_light(new Ambient(1, 1, 1, .3));
  add_light(new Point(green, .5, Point3D(0,4,10)));

  std::random_device rd; // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generator
  std::uniform_int_distribution<> distr(1, 100); // define the range

  set_acceleration(new BVH());

  int count = 0;
  for (int x = -8; x <= 8; x += 4) {
    for (int y = -8; y <= 8; y += 4) {
        if(count%2==0){
            Matte *matte_material1 = new Matte();
            matte_material1->set_ka(.8);
            matte_material1->set_kd(.8);
            matte_material1->set_cd(RGBColor((x + 8.0) / 16.0, 0, (y + 8.0) / 16.0));
            Sphere* sphere_ptr = new Sphere(Point3D(x, y, 0), 1);
            sphere_ptr->set_material(matte_material1);
            accel_ptr->add_object(sphere_ptr);
        }else{
            Reflective *reflective_material = new Reflective();
            reflective_material->set_ka(.3);
            reflective_material->set_kd(.3);
            reflective_material->set_cd(RGBColor((x + 8.0) / 16.0, 0, (y + 8.0) / 16.0));
            reflective_material->set_cr(1);
            reflective_material->set_kr(1);
            Sphere* sphere_ptr = new Sphere(Point3D(x, y, 0), 1);
            sphere_ptr->set_material(reflective_material);
            accel_ptr->add_object(sphere_ptr);
        }
        count++;
    }
  }


  Matte *matte_material = new Matte();
  matte_material->set_ka(.5);
  matte_material->set_kd(.5);
  matte_material->set_cd(yellow);

  Plane* plane_ptr = new Plane(Point3D(0,0,-10), Vector3D(0, 0, 1));
  plane_ptr->set_material(matte_material);  // green
  accel_ptr->add_object(plane_ptr);


  accel_ptr->initialize();
}
