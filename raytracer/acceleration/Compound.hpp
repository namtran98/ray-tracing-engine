#pragma once
#include "../Geometry/Geometry.hpp"
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

    void add_object(const Geometry* object_ptr);

    virtual void set_material(const Material* mPtr);

    virtual bool hit(const Ray& ray, double& t_min, ShadeInfo& s) const;

    virtual bool shadow_hit(const Ray& ray, double& t_min) const;
}