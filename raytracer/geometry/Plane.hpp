#pragma once
#include "Geometry.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"



/**
   This file declares the Plane class which represents a plane defined by an
   included point and its normal.

   Courtesy Kevin Suffern.
*/

class Plane: public Geometry {
protected:
  Point3D a;  // point on the plane.
  Vector3D n;  // normal to the plane, store as unit vector.
	
public:
  // Constructors.
  Plane();  // set plane to xz-plane.
  Plane(const Point3D& pt, const Vector3D& normal);  // set a; n parallel to normal.

  // Copy constructor and assignment operator.
  Plane(const Plane& object);
  Plane& operator=(const Plane& rhs);
	
  // Destructor.
  virtual ~Plane();	
  
  // Virtual copy constructor.
  virtual Plane* clone() const;

   // Get/set material.
  virtual std::unique_ptr<Material> get_material() const;
  virtual void set_material(std::unique_ptr<Material> mPtr);


  // Ray intersection. Set t and sinfo as per intersection with this object.
  virtual bool hit(const Ray& ray, float& t, ShadeInfo& s) const;
};
