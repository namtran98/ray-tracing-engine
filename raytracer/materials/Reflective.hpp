#pragma once
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/RGBColor.hpp"
#include "Material.hpp"
#include "../brdfs/PerfectSpecular.hpp"

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
    virtual RGBColor shade(const ShadeInfo& sinfo) const;

    void set_kr(const float k);

    void set_cr(const RGBColor& c);

    void set_cr(const float r, const float g, const float b);

    void set_cr(const float c);

  private:
    PerfectSpecular* reflective_brdf;
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
