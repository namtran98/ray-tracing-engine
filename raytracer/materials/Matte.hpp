#pragma once
// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Material.hpp"
#include "../brdfs/Lambertian.hpp"
#include "../utilities/ShadeInfo.hpp"

//----------------------------------------------------------------------------- class Matte
class Matte: public Material {
	public:

		Matte();
    Matte(const Matte& m);
    ~Matte();

		virtual Material*
		clone(void) const;

		Matte& operator= (const Matte& rhs);


		void set_ka(const float k);
		void set_kd(const float k);
		void set_cd(const RGBColor c);
		void set_cd(const float r, const float g, const float b);
		void set_cd(const float c);

		virtual RGBColor
		shade(const ShadeInfo& sr) const;

	private:

		Lambertian*		ambient_brdf;
		Lambertian*		diffuse_brdf;
};


