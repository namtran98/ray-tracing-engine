#include "Sampler.hpp"
#include "../world/ViewPlane.hpp"
#include "../utilities/Constants.hpp"
#include <cmath>
#include <algorithm>

Sampler::Sampler(){
    camera_ptr = nullptr;
    viewplane_ptr = nullptr;
    count = 0;
}  // initializes members to NULL.
Sampler::Sampler(Camera* c_ptr, ViewPlane* v_ptr){
    camera_ptr = c_ptr;
    viewplane_ptr = v_ptr;
    count = 0;
}  // set members.

Sampler::Sampler(Camera* c_ptr, ViewPlane* v_ptr, int _num_samples, int _num_sets): num_samples(_num_samples), num_sets(_num_sets), count(0){
  camera_ptr = c_ptr;
  viewplane_ptr = v_ptr;
}
// Copy constuctor and assignment operator.
Sampler::Sampler(const Sampler& camera){
    camera_ptr = camera.camera_ptr;
    viewplane_ptr = camera.viewplane_ptr;
}

Sampler& Sampler::operator= (const Sampler& other){
    this->camera_ptr = other.camera_ptr;
    this->viewplane_ptr = other.viewplane_ptr;
    return *this;
}

Point3D Sampler::screenCoordsToPoint(float px, float py) const{
  float pixelWidth = (viewplane_ptr-> bottom_right.x - viewplane_ptr->top_left.x)/viewplane_ptr->hres;
  float pixelHeight = (viewplane_ptr->top_left.y - viewplane_ptr->bottom_right.y)/viewplane_ptr->vres;
  Point3D point = Point3D(px * pixelWidth + (viewplane_ptr->top_left.x), py * pixelHeight + (viewplane_ptr->bottom_right.y), viewplane_ptr->top_left.z-kEpsilon);
  return point;
}

// Desctructor.
Sampler::~Sampler(){}

void Sampler::map_samples_to_hemisphere(const float exp) {
	int size = samples.size();
	hemisphere_samples.reserve(num_samples * num_sets);

	for (int j = 0; j < size; j++) {
		float cos_phi = cos(2.0 * PI * samples[j].x);
		float sin_phi = sin(2.0 * PI * samples[j].x);
		float cos_theta = pow((1.0 - samples[j].y), 1.0 / (exp + 1.0));
		float sin_theta = sqrt (1.0 - cos_theta * cos_theta);
		float pu = sin_theta * cos_phi;
		float pv = sin_theta * sin_phi;
		float pw = cos_theta;
		hemisphere_samples.push_back(Point3D(pu, pv, pw));
	}
}

Point3D Sampler::sample_hemisphere(void) {
	if (count % num_samples == 0)  									// start of a new pixel
		jump = (rand() % num_sets) * num_samples;
	return (hemisphere_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}

void Sampler::setup_shuffled_indices(void) {
	shuffled_indices.reserve(num_samples * num_sets);
  std::vector<int> indices;

	for (int j = 0; j < num_samples; j++)
		indices.push_back(j);

	for (int p = 0; p < num_sets; p++) {
		random_shuffle(indices.begin(), indices.end());

		for (int j = 0; j < num_samples; j++)
			shuffled_indices.push_back(indices[j]);
	}
}
