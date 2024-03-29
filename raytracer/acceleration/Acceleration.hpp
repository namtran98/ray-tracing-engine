#pragma once
#include "../utilities/Ray.hpp"
#include "../utilities/Mesh.hpp"
#include "../geometry/Geometry.hpp"
#include <vector>

using namespace std;
/**
   This file declares the Acceleration class which is an abstract class for
   acceleration structures to inherit from.
*/

class World;

class Acceleration {
protected:
  vector<Geometry*> objects;

public:
  // Constructors.
  Acceleration();

  // Copy constructor and assignment operator.
  Acceleration(const Acceleration& rhs);
  Acceleration& operator= (const Acceleration& rhs);

   // Adds objects to Compound array
  void add_object(Geometry* object_ptr); 

  int get_num_objects();

   virtual void add_from_mesh(Mesh* m_ptr, Material* mat) = 0;

    // for use with add_from_mesh
    virtual void compute_normals(Mesh* m_ptr) = 0;

  virtual void initialize() = 0;

  // Desctructor.
  virtual ~Acceleration(void);  // dummy function.

  // Normalized direction vector from light source to hit point.
  virtual bool hit(const Ray& ray, ShadeInfo& sinfo) const = 0;
};

//  LocalWords:  destructor
