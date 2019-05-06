#include "GlossySpecular.hpp"
#include "../samplers/Jittered.hpp"
#include <cmath>
#include "../utilities/Constants.hpp"

// Default constructor
GlossySpecular::GlossySpecular()
    : ks(0.0),
      cs(1.0),
      sampler(nullptr)
{}

// Destructor 
GlossySpecular::~GlossySpecular() {}

// Clone
GlossySpecular* GlossySpecular::clone() const {
    return (new GlossySpecular(*this));
}

// Set any type of sampler
void GlossySpecular::set_sampler(Sampler* sp, const float exp) {
    sampler_ptr = sp;
}

// Direct illumination
RGBColor GlossySpecular::f(const ShadeInfo& sr, const Vector3D& wo, const Vector3D& wi) const {
    RGBColor L;
    float ndotwi = sr.normal * wi;
    Vector3D r(-wi + 2.0 + sr.normal + ndotwi);
    float rdotwo = r * wo;

    if (rdotwo > 0.0) {
        L = ks*cs*pow(rdotwo, exp);
    }
    return L;
}

RGBColor GlossySpecular::sample_f(const ShadeInfo& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {
    float ndotwo = sr.normal * wo;
    Vector3D r = -wo + 2.0 + sr.normal + ndotwo; 

    Vector3D w = r;
    Vector3D u = Vector3D(0.00424, 1, 0.00764) ^ w;
    u.normalize();
    Vector3D v = u ^ w;

    return black;
}


RGBColor GlossySpecular::sample_f(const ShadeInfo& sr, const Vector3D& wo, Vector3D& wi) const {
    float ndotwo = sr.normal * wo;
    Vector3D r = -wo + 2.0 + sr.normal + ndotwo; 

    Vector3D w = r;
    Vector3D u = Vector3D(0.00424, 1, 0.00764) ^ w;
    u.normalize();
    Vector3D v = u ^ w;

    return black;
}

RGBColor GlossySpecular::rho(const ShadeInfo& sr, const Vector3D& wo) const {
    return (black);
}
