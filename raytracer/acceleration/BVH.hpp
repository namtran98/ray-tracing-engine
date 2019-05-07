#pragma once
#include "BBox.hpp"
#include "../utilities/Mesh.hpp"
#include "BBox.hpp"
#include "Acceleration.hpp"
class BVH : public Acceleration {
public:
  BVH();
  BVH(int split);
  BVH(int split, BVH *left, BVH *right);
  ~BVH();
  virtual BVH* clone();
  virtual void add_from_mesh(Mesh* m_ptr, Material* mat);
  // for use with add_from_mesh
  virtual void compute_normals(Mesh* m_ptr);

  virtual void initialize();

  virtual bool hit(const Ray& ray, ShadeInfo& sinfo) const;
private:
  unsigned int split_dim;
  BBox bbox;
  BVH *left;
  BVH *right;
  Point3D min_coordinates();      // compute minimum grid coordinates
  Point3D max_coordinates();      // compute maximum grid coordinates
};
