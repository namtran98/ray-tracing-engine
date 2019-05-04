#pragma once
#include "Sampler.hpp"
#include <memory>
/**
   This file declares the Simple class which represents a simple sampler.

   It shoots a single ray of weight 1 through a pixel.

   Courtesy Kevin Suffern.
*/

class Simple: public Sampler {
public:
  // Constructors.
  Simple();  // initializes members to NULL.
  Simple(Camera* c_ptr, ViewPlane* v_ptr);  // set members.

  // Copy constuctor and assignment operator.
  Simple(const Simple& camera);
  Simple& operator= (const Simple& other);

  // Virtual copy constructor.
  virtual Simple* clone() const;

  // Desctructor.
  virtual ~Simple();

  // Shoot a ray of weight 1 through the center of the pixel.
  virtual std::vector<Ray> get_rays(int px, int py);
};
