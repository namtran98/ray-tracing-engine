#pragma once
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/RGBColor.hpp"
#include "Material.hpp"
#include "../brdfs/PerfectSpecular.hpp"
#include "../brdfs/Lambertian.hpp"

/**
   This file declares the Material class which is an abstract class for concrete
   materials to inherit from.

   Courtesy Kevin Suffern.
*/

class Reflective: public Material {
  public:
    // Constructors.
    Reflective();  // does nothing.

    // Copy constuctor and assignment operator.
    Reflective(const Reflective& other);
    Reflective& operator=(const Reflective& rhs);

    // Virtual copy constructor.
    virtual Reflective* clone() const;

    // Desctructor.
    virtual ~Reflective();

    // Get color.
    virtual RGBColor shade(const ShadeInfo& sinfo, std::vector<int> shadows) const;

    void set_kr(const float k);
    void set_cr(const RGBColor& c);
    void set_cr(const float r, const float g, const float b);
    void set_cr(const float c);

    void set_ka(const float k);
		void set_kd(const float k);
		void set_cd(const RGBColor c);
		void set_cd(const float r, const float g, const float b);
		void set_cd(const float c);

  private:
    PerfectSpecular* reflective_brdf;
    Lambertian*		ambient_brdf;
		Lambertian*		diffuse_brdf;
};

inline void Reflective::set_kr(const float k) {
  reflective_brdf->set_kr(k);
}

inline void Reflective::set_cr(const RGBColor& c) {
  reflective_brdf->set_cr(c);
}

inline void Reflective::set_cr(const float r, const float g, const float b) {
  reflective_brdf->set_cr(r, g, b);
}

inline void Reflective::set_cr(const float c) {
  reflective_brdf->set_cr(c);
}

// ---------------------------------------------------------------- set_ka
// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection
// is diffuse reflection

inline void Reflective::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}


// ---------------------------------------------------------------- set_kd
// this also sets Lambertian::kd, but for a different Lambertian object

inline void Reflective::set_kd (const float kd) {
	diffuse_brdf->set_kd(kd);
}


// ---------------------------------------------------------------- set_cd

inline void Reflective::set_cd(const RGBColor c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}


// ---------------------------------------------------------------- set_cd

inline void Reflective::set_cd(const float r, const float g, const float b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}

// ---------------------------------------------------------------- set_cd

inline void Reflective::set_cd(const float c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}
