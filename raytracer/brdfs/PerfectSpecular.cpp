#include "PerfectSpecular.hpp"
#include "../utilities/Constants.hpp"
#include <cmath>

// Default constructor

PerfectSpecular::PerfectSpecular()
	: 	BRDF(),
		kr(0.0),
		cr(1.0)
{}

// Destructor

PerfectSpecular::~PerfectSpecular(void) {}

// Clone fn
PerfectSpecular*
PerfectSpecular::clone(void) const {
	return (new PerfectSpecular(*this));
}

// f function
RGBColor
PerfectSpecular::f(const ShadeInfo& sr, const Vector3D& wo, const Vector3D& wi) const {
	return (black);
}

RGBColor
PerfectSpecular::sample_f(const ShadeInfo& sr, const Vector3D& wo, Vector3D& wi) const {
	float ndotwo = sr.normal * wo;
	wi = -wo + 2.0 * sr.normal * ndotwo;
	return (kr * cr / fabs(sr.normal * wi)); // why is this fabs? // kr would be a Fresnel term in a Fresnel reflector
}

RGBColor
PerfectSpecular::sample_f(const ShadeInfo& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {
    float ndotwo = sr.normal * wo;
    wi = -wo + 2.0 * sr.normal * ndotwo;
	pdf = fabs(sr.normal * wi);
	return (kr * cr);
}

RGBColor
PerfectSpecular::rho(const ShadeInfo& sr, const Vector3D& wo) const {
	return (black);
}
