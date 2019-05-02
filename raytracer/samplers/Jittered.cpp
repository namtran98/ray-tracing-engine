#include "Jittered.hpp"
#include "../utilities/Constants.hpp"
#include <cmath>


Jittered::Jittered(){
  camera_ptr = nullptr;
  viewplane_ptr = nullptr;

  // Reasonable defaults (83 suggested in the textbook)
  num_samples = 4;
  num_sets = 83;
  count = 0;
  generateSamples();
}
Jittered::Jittered(Camera* c_ptr, ViewPlane* v_ptr, int _num_samples, int _num_sets): Sampler(c_ptr, v_ptr), num_samples(_num_samples), num_sets(_num_sets), count(0) {
  generateSamples();
}

// Copy constuctor and assignment operator.
Jittered::Jittered(const Jittered& other){
  camera_ptr = other.camera_ptr;
  viewplane_ptr = other.viewplane_ptr;
  num_samples = other.num_samples;
  num_sets = other.num_sets;
  count = other.count;
  samples = other.samples;
}

Jittered& Jittered::operator= (const Jittered& other){
  camera_ptr = other.camera_ptr;
  viewplane_ptr = other.viewplane_ptr;
  num_samples = other.num_samples;
  num_sets = other.num_sets;
  count = other.count;
  samples = other.samples;
  return *this;
}

// Virtual copy constructor.
Jittered* Jittered::clone() const{
  return new Jittered(*this);
}

// Desctructor.
Jittered::~Jittered(){}

// Shoot a ray of weight 1 through the center of the pixel.
std::vector<Ray> Jittered::get_rays(int px, int py) {
  std::vector<Ray> rays;
  for(int i = 0; i < num_samples; i++){
    Point2D sample = samples[count++ % (num_samples * num_sets)];
    Point3D point = screenCoordsToPoint(px + sample.x, py + sample.y);
    rays.push_back(Ray(point, camera_ptr->get_direction(point)));
  }
  return rays;
}

inline float rand_float() {
  return (float) rand() * invRAND_MAX;
}

void Jittered::generateSamples(){
  int n = (int) sqrt(num_samples);
  for (int p = 0; p < num_sets; p++){
    for (int j = 0; j < n; j++){
      for (int k = 0; k < n; k++){
        Point2D sp;
        sp.x = (k + rand_float()) / n;
        sp.y = (j + rand_float()) / n;
        samples.push_back(sp);
      }
    }
  }
}


