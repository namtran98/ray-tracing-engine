#pragma once
#include "../materials/Material.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../acceleration/BBox.hpp"
#include <memory>
/**
   This file declares the Geometry class which is an abstract class from which
   other concrete geometric objects will inherit.

   Courtesy Kevin Suffern.
*/

class Geometry {
protected:
  mutable Material* material_ptr;  // this object's material 
                                   // mutable for const functions in Compoun
  BBox bbox;

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
  virtual Material* get_material() const;
  virtual void set_material(Material* mPtr);

  // Makes it possible to get BBox dimensions on a Geometry Object
  virtual BBox get_bounding_box();

  // Makes it possible to add_objects with Compound objects
  void add_object(Geometry* object_ptr) {}

  // Ray intersection. Set t and sinfo as per intersection with this object.
  virtual bool hit(const Ray& ray, float& t, ShadeInfo& sinfo) const = 0;
};
