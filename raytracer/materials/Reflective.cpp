#include "Reflective.hpp"
#include "../world/World.hpp"

// Default constructors.
Reflective::Reflective()
    : Material(),
      reflective_brdf(new PerfectSpecular)
{} 

// Copy constructor 
Reflective::Reflective(const Reflective& rm) 
    : Material(rm) {
    if (rm.reflective_brdf) {
        reflective_brdf = rm.reflective_brdf->clone();
    }
    else {
        reflective_brdf = nullptr;
    }
}

// Assignment operator
Reflective& Reflective::operator= (const Reflective& rhs) {
    if (this == &rhs) {
        return (*this);
    }

    Material::operator=(rhs);

    if (reflective_brdf) {
        delete reflective_brdf;
        reflective_brdf = nullptr;
    }

    if (rhs.reflective_brdf) {
        reflective_brdf = rhs.reflective_brdf->clone();
    }

    return (*this);
}

// Clone
Reflective* Reflective::clone() const {
    return (new Reflective(*this));
}

// Destructor
Reflective::~Reflective() {
    if (reflective_brdf) {
        delete reflective_brdf;
        reflective_brdf = NULL;
    }
}

// shade
RGBColor Reflective::shade(const ShadeInfo& sr) const {
    RGBColor L(Material::shade(sr));

    Vector3D wo = -sr.ray.d;
    Vector3D wi;
    RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);

    Ray reflected_ray(sr.hit_point, wi);
    reflected_ray.w = sr.depth + 1;

    // I removed the depth thing here bc i guess this ray should have some sort of depth 
    L += fr * (sr.w->tracer_ptr->trace_ray(reflected_ray)) * (sr.normal * wi);

    return (L);
}


