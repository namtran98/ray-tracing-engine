#pragma once
#include "../utilities/Ray.hpp"

/**
   This file declares the Acceleration class which is an abstract class for
   acceleration structures to inherit from.
*/

class Acceleration {
public:
  // Constructors.
  Acceleration();  // set color to white (1, 1, 1).

  // Copy constructor and assignment operator.
  Acceleration(const Acceleration& rhs);
  Acceleration& operator= (const Acceleration& rhs);

  // Virtual copy constructor.

  // Desctructor.
  virtual ~Acceleration(void);  // dummy function.


  // Normalized direction vector from light source to hit point.
  virtual bool hit(const Ray& ray) const = 0;
};
