#pragma once
#include "Sampler.hpp"
#include <vector>

class Jittered : public Sampler {
public:
  Jittered();
  Jittered(Camera* c_ptr, ViewPlane* v_ptr, int num_samples, int num_sets);

  // Copy constuctor and assignment operator.
  Jittered(const Jittered& camera);
  Jittered& operator= (const Jittered& other);

  // Virtual copy constructor.
  virtual Jittered* clone() const;

  // Desctructor.
  virtual ~Jittered();

  // Shoot a of weight 1 through the center of the pixel.
  virtual std::vector<Ray> get_rays(int px, int py);

  void generateSamples();
};
