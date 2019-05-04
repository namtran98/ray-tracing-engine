#pragma once
#include "../Geometry/Geometry.hpp"
#include <vector>

using namespace std;

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
    vector<Geometry*> objects;
    
public:
  // Constructors.
  Compound(); 

  // Copy constructor and assignment operator.
  Compound(const Compound& object);
  Compound& operator= (const Compound& rhs);

  // Destructor.
  virtual ~Compound();

  // Virtual copy constructor.
  virtual Compound* clone() const;

  // Adds objects to Compound array
  void add_object(Geometry* object_ptr); 

  int get_num_objects();

  // Sets material for all objects in Compound array
  virtual void set_material(Material* mPtr);

  virtual bool hit(const Ray& ray, float& t, ShadeInfo& sinfo) const;

  virtual bool shadow_hit(const Ray& ray, double& t) const;

private:
  void delete_objects();

  void copy_objects(const vector<Geometry*>& rhs);


}