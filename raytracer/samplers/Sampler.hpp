#pragma once
#include <vector>
#include "../cameras/Camera.hpp"
#include "../utilities/Ray.hpp"

/**
   This file declares the Sampler class which is an abstract class for concrete
   samplers to inherit from.

   A sampler samples a scene by shooting primary rays through pixels in a
   viewplane. A primary ray begins at the pixel and its direction is determined
   by a camera. Different samplers shoot different numbers of primary rays in
   different manners.

   Courtesy Kevin Suffern.
*/

class ViewPlane;


class Sampler {
protected:
  struct Point2D{
    float x;
    float y;
  };
  Camera* camera_ptr;  // the camera that decides the projectors.
  ViewPlane* viewplane_ptr;  // the view plane through which rays are shot.
  std::vector<Point2D>			samples;				// sample points on a unit square
  std::vector<Point3D> hemisphere_samples;

  int num_samples;
  int num_sets;
  unsigned long count;

public:
  // Constructors.
  Sampler();  // initializes members to NULL.
  Sampler(Camera* c_ptr, ViewPlane* v_ptr);  // set members.

  // Copy constuctor and assignment operator.
  Sampler(const Sampler& camera);
  Sampler& operator= (const Sampler& other);

  // Virtual copy constructor.
  virtual Sampler* clone() const = 0;

  // Desctructor.
  virtual ~Sampler();

  // Get rays corresponding to a pixel in the view plane. px and py are 0-based
  // indexes of the pixel in the view plane, with the origin at the top left of
  // the view plane.
  virtual std::vector<Ray> get_rays(int px, int py) = 0;
  Point3D screenCoordsToPoint(float px, float py) const;
  void map_samples_to_hemisphere(const float p);

};
