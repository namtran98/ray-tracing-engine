#pragma once
#include "../materials/Material.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include <memory>
/**
   This file declares the Geometry class which is an abstract class from which
   other concrete geometric objects will inherit.

   Courtesy Kevin Suffern.
*/

class Geometry {	
protected:
  std::unique_ptr<Material> material_ptr;  // this object's material.
	
public:	
  // Constructors.
  Geometry();  // sets material_ptr to NULL.

  // Copy constructor and assignment operator.
  Geometry(const Geometry& object);
  Geometry& operator= (const Geometry& rhs);
	
  // Destructor.
  virtual ~Geometry();	

  // Virtual copy constructor.
  virtual Geometry* clone() const = 0;

  // Get/set material.
  virtual std::unique_ptr<Material> get_material() const;
  virtual void set_material(std::unique_ptr<Material> mPtr);

  // Ray intersection. Set t and sinfo as per intersection with this object.
  virtual bool hit(const Ray& ray, float& t, ShadeInfo& sinfo) const = 0;
};
