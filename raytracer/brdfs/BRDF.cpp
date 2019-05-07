#include "BRDF.hpp"
#include "../utilities/Constants.hpp"

BRDF::BRDF() 
	: sampler_ptr(nullptr)
{}


BRDF::BRDF(const BRDF& brdf) {
    if (brdf.sampler_ptr) {
        sampler_ptr = brdf.sampler_ptr->clone();
    }
    else {
        sampler_ptr = nullptr;
    }
}

BRDF&														
BRDF::operator= (const BRDF& rhs) {
	if (this == &rhs)
		return (*this);
		
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if (rhs.sampler_ptr)
		sampler_ptr	= rhs.sampler_ptr->clone();

	return (*this);
}


BRDF::~BRDF(void) {
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}  

RGBColor
BRDF::f(const ShadeInfo& sr, const Vector3D& wo, const Vector3D& wi) const {
	return (black);
}

RGBColor
BRDF::sample_f(const ShadeInfo& sr, const Vector3D& wo, Vector3D& wi) const {
	return (black);
}

// ------------------------------------------------------------------------ sample_f

RGBColor
BRDF::sample_f(const ShadeInfo& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {
	return (black);
}


// ------------------------------------------------------------------------ rho	
	
RGBColor
BRDF::rho(const ShadeInfo& sr, const Vector3D& wo) const {
	return (black);
}






