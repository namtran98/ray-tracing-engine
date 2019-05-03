#pragma once
#include "../geometry/Geometry.hpp"
#include <vector>

/**
   Stores an array of geometric objects, and allows us to:
    - Treat a collection of objects as a single object 
      (apply the same transformation/material to all of them at once)
    - Build objects with more than a single component and have a named 
      type in the ray tracer

   Courtesy Kevin Suffern.
*/

class Compound: public Geometry {
protected:
    std::vector<Geometry*> objects;
    
public:
    // Constructors.
    Compound();  // sets material_ptr to NULL.

    // Copy constructor and assignment operator.
    Compound(const Compound& object);
    Compound& operator= (const Compound& rhs);

    // Destructor.
    virtual ~Compound();

    // Virtual copy constructor.
    virtual Compound* clone() const;

    void add_object(Geometry* object_ptr);    // const Geometry* object_ptr ?

    virtual void set_material(Material* mPtr);

    virtual bool hit(const Ray& ray, float& t, ShadeInfo& sinfo) const;

    virtual bool shadow_hit(const Ray& ray, double& t) const;
};