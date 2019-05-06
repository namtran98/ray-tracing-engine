#include "BRDF.hpp"
#include "../utilities/Vector3D.hpp"

class PerfectSpecular: public BRDF {
    public: 
        PerfectSpecular();

        ~PerfectSpecular();

        virtual PerfectSpecular*
		clone(void) const;
		
		void
		set_kr(const float k);
		
		void
		set_cr(const RGBColor& c);
		
		void													
		set_cr(const float r, const float g, const float b);
		
		void													
		set_cr(const float c);
		
		virtual RGBColor
		f(const ShadeInfo& sr, const Vector3D& wo, const Vector3D& wi) const;
		
		virtual RGBColor
		sample_f(const ShadeInfo& sr, const Vector3D& wo, Vector3D& wi) const;
		
		virtual RGBColor
		sample_f(const ShadeInfo& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
		
		virtual RGBColor
		rho(const ShadeInfo& sr, const Vector3D& wo) const;
				
	private:
	
		float		kr;			// reflection coefficient
		RGBColor 	cr;			// the reflection colour
};  

// -------------------------------------------------------------- set_kr

inline void
PerfectSpecular::set_kr(const float k) {
	kr = k;
}


// -------------------------------------------------------------- set_cr

inline void
PerfectSpecular::set_cr(const RGBColor& c) {
	cr = c;
}


// ---------------------------------------------------------------- set_cr

inline void													
PerfectSpecular::set_cr(const float r, const float g, const float b) {
	cr.r = r; cr.g = g; cr.b = b;
}


// ---------------------------------------------------------------- set_cr

inline void													
PerfectSpecular::set_cr(const float c) {
	cr.r = c; cr.g = c; cr.b = c;
}